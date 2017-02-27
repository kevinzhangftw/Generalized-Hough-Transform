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
#include "Inspector.hpp"

using namespace std;

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

    Mat inspectionMat;
    inspectionMat.create( edgeImage.size(), CV_32F);
    for (int i=0; i<edgeImage.cols-1; ++i) {
        for (int j=0; j<edgeImage.rows-1; ++j) {
        if ( edgeImage.at<uchar>(j,i) == 255  ) {
            float vx = dx.at<float>(j,i);
            float vy = dy.at<float>(j,i);
            Rpoint3 entry;
            //float mag = std::sqrt( float(vx*vx+vy*vy) );
            entry.dy = i - referencePoint(1);
            entry.dx = j - referencePoint(0);
            // update further right and left dx
            if (entry.dx < mindx) mindx=entry.dx;
            if (entry.dx > maxdx) maxdx=entry.dx;
            points.push_back( entry );
            const float theta = fmod(fastAtan2(vy, vx), 360);
            const float thetaScale = 360.0 / intervals;
            const int n = cvRound(theta / thetaScale) % intervals;
//            cout << "vx: " << vx << ", vy: " << vy << endl;
//            cout << "theta: " << theta << ", n: " << n << endl;
            table[n].push_back( Vec2i(entry.dx, entry.dy) );
           inspectionMat.at<float>(j, i) = theta;
        }
            

    }}
    
    wtemplate = maxdx-mindx+1;
}


Mat TableGenerator::buildAngles(Mat edgeImage, Mat dx, Mat dy){
    Mat tempMat;
    tempMat.create(edgeImage.size(), CV_32F);
    for (int i=0; i<edgeImage.cols-1; ++i) {
        for (int j=0; j<edgeImage.rows-1; ++j) {
            if ( edgeImage.at<uchar>(j,i) == 255  ) {
                float vx = dx.at<float>(j,i);
                float vy = dy.at<float>(j,i);
                const float theta = fmod(fastAtan2(vy, vx), 360);
                tempMat.at<float>(j,i) = theta;
            }
        }}
    return tempMat;
}


void TableGenerator::debugPrint(Mat matrix) {
    cout << "size: " << matrix.size << endl;
    cout << matrix << endl;
}

Mat TableGenerator::xContour(Mat grayscale){
    Mat mat;
    mat.create(grayscale.size(), CV_32F);
    Sobel(grayscale, mat, CV_32F, 1, 0, CV_SCHARR);
    return mat;
}

Mat TableGenerator::yContour(Mat grayscale){
    Mat mat;
    mat.create(grayscale.size(), CV_32F);
    Sobel(grayscale, mat, CV_32F, 0, 1, CV_SCHARR);
    return mat;
}


Mat TableGenerator::detectEdges(Mat source) {
    Mat edgeMat;
    blur( source, edgeMat, Size(3,3) );
    int thr1 = 1, thr2 = 100;
    Canny( edgeMat, edgeMat, thr1, thr2, 3 );
    return edgeMat;
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

Mat TableGenerator::phiMat(Mat source) {
    Mat blurred;
    blurred.create(source.size(), CV_32F);
    medianBlur(source, blurred, 5);
    Mat tempAngleMat;
    tempAngleMat.create(source.size(), CV_32F);
    Mat tempEdge = detectEdges(blurred);
    Mat tempDx = xContour(blurred);
    Mat tempDy = yContour(blurred);
    tempAngleMat = buildAngles(tempEdge, tempDx, tempDy);
    return tempAngleMat;
}

Rtable TableGenerator::generate(Mat gray) {
    grayImage = gray;
    
    rowCount = grayImage.rows;
    columnCount = grayImage.cols;
    edgeImage = detectEdges(grayImage);
    // for each edge point, record its angle relative to reference
    setReferencePoint();
    dx = xContour(grayImage);
    dy = yContour(grayImage);
    initRtable(intervals);
    buildRPoints();
    
    return table;
}
