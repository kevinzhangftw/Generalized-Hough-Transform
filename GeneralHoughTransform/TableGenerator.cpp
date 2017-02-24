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

void TableGenerator::inspect(Mat image) {
    debugPrint(image);
    imshow("inspecting", image);
    waitKey(0);
}

String TableGenerator::type2str(int type) {
    String r;
    
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);
    
    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }
    
    r += "C";
    r += (chans+'0');
    
    return r;
}

void TableGenerator::initRtable(int intervals){
    table.clear();
    table.resize(intervals);
}


float TableGenerator::setRange(int intervals) {
    float range;
    return range = pi/intervals;
}

void TableGenerator::setReferencePoint(){
    referencePoint[0] = rowCount/2;
    referencePoint[1] = columnCount/2;
}

void TableGenerator::buildRPoints(){
    int mindx = INT_MAX;
    int maxdx = INT_MIN;
    points.clear();

    Mat inspectionMat = Mat::zeros(edgeImage.rows, edgeImage.cols, CV_32F);
    
    inspect(dx);
    for (int i=0; i<rowCount; ++i) {
        float * xRow = dx.ptr<float>(i);
        for (int j=0; j<columnCount; ++j) {
        if ( edgeImage.at<uchar>(i, j) == 255  ) {

            float vx = dx.at<float>(i,j);
            float vy = dy.at<float>(i,j);
            Rpoint3 entry;
            //float mag = std::sqrt( float(vx*vx+vy*vy) );
            entry.dx = referencePoint(0)-j;
            entry.dy = referencePoint(1)-i;
            
            inspectionMat.at<float>(i, j) = xRow[j];
            
            /*
             const float theta = fastAtan2(dyRow[x], dxRow[x]);
             const int n = cvRound(theta * thetaScale);
             r_table_[n].push_back(p - templCenter_);
             */
            
            float theta = fastAtan2(vy, vx);
            float a = atan2((float)vy, (float)vx); //radians
            entry.phi = ((a > 0) ? a-pi/2 : a+pi/2);
            //float a = atan2((float)vy, (float)vx) * 180/3.14159265358979f; //degrees
            //rpt.phi = ((a > 0) ? a-90 : a+90);
            // update further right and left dx
            if (entry.dx < mindx) mindx=entry.dx;
            if (entry.dx > maxdx) maxdx=entry.dx;
            points.push_back( entry );
//            inspectionMat.at<uchar>(i, j) = 255;
            inspectionMat.at<float>(i, j) = entry.phi;
        }
    }}
    inspect(inspectionMat);
    wtemplate = maxdx-mindx+1;
}

void TableGenerator::debugPrint(Mat matrix) {
    cout << "size: " << matrix.size << endl;
    cout << matrix << endl;
}

void TableGenerator::setXContour(){
    dx.create( Size(columnCount, rowCount), CV_32F);
    Sobel(edgeImage, dx, CV_32F, 1, 0, CV_SCHARR);
}

void TableGenerator::setYContour(){
    dy.create( Size(columnCount, rowCount), CV_32F);
    Sobel(edgeImage, dy, CV_32F, 0, 1, CV_SCHARR);
//    debugPrint(dy);
//    inspect(dy);
}


Mat TableGenerator::detectEdges(Mat source) {
    Mat edgeMat;
    blur( source, edgeMat, Size(3,3) );
    int thr1 = 1, thr2 = 100;
    Canny( edgeMat, edgeMat, thr1, thr2, 3 );
    return edgeMat;
}

void TableGenerator::allotPoints() {
    // put points in the right interval, according to discretized angle and range size
    float range = setRange(intervals);
    for (int t = 0; t < points.size(); ++t){
        int angleindex = (int)((points[t].phi+pi/2)/range);
        if (angleindex == intervals) angleindex=intervals-1;
        table[angleindex].push_back( Vec2i(points[t].dx, points[t].dy) );
    }
}

void TableGenerator::inspectTable(Rtable table) {
    for (int i = 0; i < table.size(); i++) {
        cout << "interval " << i << ":" << endl;
        std::vector<Vec2i> entries = table[i];
        for (int j = 0; j < entries.size(); j++) {
            cout << "dx: " << entries[j](0) << " ";
            cout << "dy: " << entries[j](1) << endl;
        }
    }
    cout << "end interval" << endl;
}

Rtable TableGenerator::generate(Mat grayImage) {
    this->grayImage = grayImage;
    matType = grayImage.type();
    rowCount = grayImage.rows;
    columnCount = grayImage.cols;
    edgeImage = detectEdges(grayImage);

    // for each edge point, record its angle relative to reference
    setReferencePoint();
    setXContour();
    setYContour();
    buildRPoints();
    
//    inspect(dx);
//    inspect(dy);
    
    // put into buckets
    intervals = 16;
    initRtable(intervals);
    allotPoints();
    
    inspectTable(table);
    // load points on vector

    
    return Rtable();
}
