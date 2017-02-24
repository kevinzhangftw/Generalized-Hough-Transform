//
//  MatrixAccess.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-22.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "MatrixAccess.hpp"
#define CV_8U   0
#define CV_8S   1
#define CV_16U  2
#define CV_16S  3
#define CV_32S  4
#define CV_32F  5
#define CV_64F  6
#define CV_USRTYPE1 7


void MatrixAccess::access(String source) {
    cout << "image accessed:" << source << endl;
    Mat matrix = imread(source, CV_RGB2GRAY);
    
    int pixel = (int)matrix.at<uchar>(10,10);
    cout << "pixel output at 10,10 is:" << pixel << endl;
}

void MatrixAccess::copy(Mat original){
    
}
