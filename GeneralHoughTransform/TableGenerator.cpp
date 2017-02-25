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
#include "MatrixAccess.hpp"

using namespace std;

void TableGenerator::inspect(Mat image) {
//    debugPrint(image);
    normalize(image, image, 0, 1, NORM_MINMAX, CV_32F);
    imshow("inspecting", image);
    cout << "Mat Type:" << image.type() << endl;
    imwrite( "../output/inspection.jpg", image );
    waitKey(0);
}

void TableGenerator::inspectGray(Mat image) {
    debugPrint(image);
    Mat grayCopy = Mat::zeros(image.size(), CV_32F);
    double min, max;
    cv::minMaxLoc(image, &min, &max);
    float range = max - min;
    for (int i = 0; i < image.cols; i++) {
        for (int j = 0; j < image.rows; j++) {
            grayCopy.at<float>(i, j) = (image.at<float>(i,j) - (float) min) / (float) range;
        }
    }
    debugPrint(grayCopy);
    imshow("inspecting grayCopy", grayCopy);
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

void TableGenerator::normFloat(Mat &mat) {
    normalize(mat, mat, 0, 1, NORM_MINMAX, CV_32F);

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

//    inspect(edgeImage); 
    Mat inspectionMat;
    inspectionMat.create( edgeImage.size(), CV_32F);
    for (int i=0; i<dx.cols-1; ++i) {
        for (int j=0; j<dx.rows-1; ++j) {
        if ( edgeImage.at<uchar>(j,i) == 255  ) {
            float vx = dx.at<float>(j,i);
            float vy = dy.at<float>(j,i);
            Rpoint3 entry;
            //float mag = std::sqrt( float(vx*vx+vy*vy) );
            entry.dy = i - referencePoint(1);
            entry.dx = j - referencePoint(0);
            
            /*
             const float theta = fastAtan2(dyRow[x], dxRow[x]);
             const int n = cvRound(theta * thetaScale);
             r_table_[n].push_back(p - templCenter_);
             */
            
            
            // update further right and left dx
            if (entry.dx < mindx) mindx=entry.dx;
            if (entry.dx > maxdx) maxdx=entry.dx;
            points.push_back( entry );
            const float theta = fmod(fastAtan2(vy, vx), 360);
            const float thetaScale = 360.0 / intervals;
            const int n = cvRound(theta / thetaScale) % intervals;
            cout << "vx: " << vx << ", vy: " << vy << endl;
            cout << "theta: " << theta << ", n: " << n << endl;
            table[n].push_back( Vec2i(entry.dx, entry.dy) );
           inspectionMat.at<float>(j, i) = theta;
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
    Sobel(grayImage, dx, CV_32F, 1, 0, CV_SCHARR);
    
}

void TableGenerator::setYContour(){
    dy.create( Size(columnCount, rowCount), CV_32F);
    Sobel(grayImage, dy, CV_32F, 0, 1, CV_SCHARR);
}


Mat TableGenerator::detectEdges(Mat source) {
    Mat edgeMat;
    blur( source, edgeMat, Size(3,3) );
    int thr1 = 1, thr2 = 100;
    Canny( edgeMat, edgeMat, thr1, thr2, 3 );
    return edgeMat;
}

void TableGenerator::allotPoints() {
    // r_table_[n].push_back
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
            cout << "(" << entries[j](0) << " ";
            cout << entries[j](1) << ")" << ", ";
        }
        cout << endl;
    }
    cout << "end intervals" << endl;
}

Rtable TableGenerator::generate(Mat gray) {
    grayImage = gray;
    
    rowCount = grayImage.rows;
    columnCount = grayImage.cols;
    edgeImage = detectEdges(grayImage);
    // for each edge point, record its angle relative to reference
    setReferencePoint();
    setXContour();
    setYContour();
    intervals = 16;
    initRtable(intervals);
    buildRPoints();
    
    
    // put into buckets
    
    inspectTable(table);
    // load points on vector

    
    return Rtable();
}
