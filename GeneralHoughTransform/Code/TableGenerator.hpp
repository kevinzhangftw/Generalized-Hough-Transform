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
#include "Rtable.hpp"

using namespace cv;

typedef std::vector<std::vector<Vec2i>> Rtable;
typedef unsigned char uchar;

struct Rpoint3{
    int dx;
    int dy;
    float phi;
};

class TableGenerator {
    int rowCount;//= template_img.rows;
    int columnCount;//= template_img.cols;
    int matType;
    Mat grayImage;
    Mat edgeImage;
    void normFloat(Mat &mat);
    void setReferencePoint();
    Vec2i referencePoint;
    Mat dx;
    Mat dy;
    Mat xContour(Mat grayscale);
    Mat yContour(Mat grayscale);
    void buildRPoints();
    std::vector<Rpoint3> points;
    ////////
    String type2str(int type);
    
    void initRtable(int intervals);
    void readRtable();
    int intervals = 60;
    Rtable table;
    float setRange(int intervals);
    const float pi = 3.14159265f;
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
    void debugPrint(Mat matrix);
    Mat buildAngles(Mat edgeImage, Mat dx, Mat dy);
public:
    Mat detectEdges(Mat source);
    
    void inspectTable(Rtable table);
    Rtable generate(Mat grayImage);
    Mat phiMat(Mat source);
};

#endif /* TableGenerator_hpp */
