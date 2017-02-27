//
//  VoteAccumulator.hpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-24.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#ifndef VoteAccumulator_hpp
#define VoteAccumulator_hpp

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <thread>
#include <string>
#include <iostream>
#include "Rtable.hpp"

using namespace cv;

class VoteAccumulator {
    float minScale = 1;
    float maxScale = 1.05;
    float scaleStep = 0.05;
    int wiggleMin = -5; //angle delta in degrees
    int wiggleMax = 15; //angle delta in degrees
    int intervals = 60;
    float threshold = 0.55 ;
public:
    Mat accumulate(Mat edgeMat, Mat phiMat, Rtable table);
    

    
};


#endif /* VoteAccumulator_hpp */
