//
//  TableGenerator.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-17.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//
#include "TableGenerator.hpp"
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>


using namespace std;

void TableGenerator::initRtable(int intervals){
    table.clear();
    table.resize(intervals);
}


float TableGenerator::setRange(int intervals) {
    float range;
    return range = pi/intervals;
}


Vec2i TableGenerator::getRefPoint(Mat template_img){
//    Mat template_img = imread("files\contour_rough.bmp", 1);
    Vec2i referencePoint;
    // find reference point inside contour image and save it in variable refPoint
    for (int j=0; j<rowCount; ++j) {
        Vec3b* data= (Vec3b*)(template_img.data + template_img.step.p[0]*j);
        for (int i=0; i<columnCount; ++i) {
            if ( data[i]==Vec3b(127,127,127)  ){
                referencePoint = Vec2i(i,j);
            }
        }
    }
    return referencePoint;
}

void TableGenerator::buildRtable(int nl, int nc, int mindx, int maxdx, Mat dx, Mat dy, Mat template_img){
    for (int j=0; j<nl; ++j) {
        Vec3b* data= (Vec3b*)(template_img.data + template_img.step.p[0]*j);
        for (int i=0; i<nc; ++i) {
            if ( data[i]==Vec3b(255,255,255)  )
            {
                short vx = dx.at<short>(j,i);
                short vy = dy.at<short>(j,i);
                Rpoint3 rpt;
                //float mag = std::sqrt( float(vx*vx+vy*vy) );
                rpt.dx = refPoint(0)-i;
                rpt.dy = refPoint(1)-j;
                float a = atan2((float)vy, (float)vx); //radians
                rpt.phi = ((a > 0) ? a-pi/2 : a+pi/2);
                //float a = atan2((float)vy, (float)vx) * 180/3.14159265358979f; //degrees
                //rpt.phi = ((a > 0) ? a-90 : a+90);
                // update further right and left dx
                if (rpt.dx < mindx) mindx=rpt.dx;
                if (rpt.dx > maxdx) maxdx=rpt.dx;
                pts.push_back( rpt );
            }
        }
    }
}

void TableGenerator::readPoints(Mat edgeImage, Mat grayImage){
    Mat template_img = edgeImage;
    // find reference point inside contour image and save it in variable refPoint
    
    
    // get Scharr matrices from original template image to obtain contour gradients
    Mat dx = getDx(grayImage);
    Mat dy = getDy(grayImage);
    
    // load points on vector
    pts.clear();
    int mindx = INT_MAX;
    int maxdx = INT_MIN;
    buildRtable(rowCount, columnCount, mindx, maxdx, dx, dy, template_img);
    // maximum width of the contour
    wtemplate = maxdx-mindx+1;
}


Mat TableGenerator::getDx(Mat grayImage){
    Mat dx;
    dx.create( Size(grayImage.cols, grayImage.rows), CV_16SC1);
    Sobel(grayImage, dx, CV_16S, 1, 0, CV_SCHARR);
    return dx;
}

Mat TableGenerator::getDy(Mat grayImage){
    Mat dy;
    dy.create( Size(grayImage.cols, grayImage.rows), CV_16SC1);
    Sobel(grayImage, dy, CV_16S, 0, 1, CV_SCHARR);
    return dy;
}


Mat TableGenerator::detectEdges(Mat source) {
    Mat edgeMat;
    blur( source, edgeMat, Size(3,3) );
    int thr1 = 1, thr2 = 100;
    Canny( edgeMat, edgeMat, thr1, thr2, 3 );
    return edgeMat;
}


// create Rtable from contour points
void TableGenerator::readRtable() {
    initRtable(intervals);
    // put points in the right interval, according to discretized angle and range size
    float range = setRange(intervals);
    for (vector<Rpoint3>::size_type t = 0; t < pts.size(); ++t){
        int angleindex = (int)((pts[t].phi+pi/2)/range);
        if (angleindex == intervals) angleindex=intervals-1;
//        Rtable[angleindex].push_back( Vec2i(pts[t].dx, pts[t].dy) );
    }
}


Rtable TableGenerator::generate(Mat grayImage) {
    rowCount = grayImage.rows;
    columnCount = grayImage.cols;
    Mat edgeImage = detectEdges(grayImage);
    //TODO: getRefPoint
    refPoint = getRefPoint(edgeImage);
    
    
    return Rtable();
}
