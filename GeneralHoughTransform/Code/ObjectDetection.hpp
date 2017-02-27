//
//  ObjectDetection.hpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-17.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#ifndef ObjectDetection_hpp
#define ObjectDetection_hpp

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <thread>
#include <string>
#include <iostream>
#include "TableGenerator.hpp"
#include "VoteAccumulator.hpp"

using namespace cv;

class ObjectDetection {
    
    Mat grayScaleOf(String object);
public:
    Mat detect(String, String);
    
};

#endif /* ObjectDetection_hpp */
