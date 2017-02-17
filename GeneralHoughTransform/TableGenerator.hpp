//
//  TableGenerator.hpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-17.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#ifndef TableGenerator_hpp
#define TableGenerator_hpp

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <thread>
#include <string>
#include <iostream>

using namespace cv;

typedef std::vector<std::vector<Vec2i>> Rtable;


struct Rpoint3{
    float dx;
    float dy;
    int phi;
};

class TableGenerator {
    int rowCount;//= template_img.rows;
    int columnCount;//= template_img.cols;
    
    //
    Vec2i getRefPoint(Mat template_img);
    void initRtable(int intervals);
    void readRtable();
    void readPoints(Mat edgeImage, Mat grayImage);
    int intervals;
    Vec2i refPoint;
    Rtable table;
    float setRange(int intervals);
    const float pi = 3.14159265f;
    std::vector<Rpoint3> pts;
    // width of template contour
    int wtemplate;
    // minimum and maximum width of scaled contour
    int wmin;
    int wmax;
    // minimum and maximum rotation allowed for template
    float phimin;
    float phimax;
    // dimension in pixels of squares in imagete
    int rangeXY;
    // interval to increase scale
    int rangeS;
    Mat getDx(Mat grayImage);
    Mat getDy(Mat grayImage);
    void buildRtable(int nl, int nc, int mindx, int maxdx, Mat dx, Mat dy, Mat template_img);
    Mat detectEdges(Mat source);
public:
    Rtable generate(Mat grayImage);
};

#endif /* TableGenerator_hpp */
