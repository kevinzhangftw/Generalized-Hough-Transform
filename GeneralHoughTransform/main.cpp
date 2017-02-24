//
//  main.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-10.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>
#include "GHT.cpp"
#include "ObjectDetection.hpp"
#include "MatrixAccess.hpp"

using namespace cv;
using namespace std;

void runGHT(char c){
    //c = 't'; // create template
    //c = 'r'; // run algorithm
    if (c == 't'){
        GenHoughTrnf ght;
        ght.createTemplate();
    } else if (c == 'r'){
        GenHoughTrnf ght;
        //ght.setTresholds(180, 250);
        ght.createRtable();
        //Mat detect_img = imread("files\\Img_01.png", 1);
        Mat detect_img = imread("animals.jpg", 1);
        //Mat detect_img = imread("files\\Img_03.png", 1);
        ght.accumulate(detect_img);
        ght.bestCandidate();
    }
}

int main(int argc, const char * argv[]) {
//    runGHT('t');
    
    //real thing
//    ObjectDetection detector = ObjectDetection();
//    Mat detectedBear = detector.detect("animals", "block");
//    imshow("block", detectedBear);
//    waitKey(0);
    //
    MatrixAccess MatrixAccess;
    MatrixAccess.access("template_bear.png");
    
//    Mat detectedElephant = detector.detect("animals", "elephant");
//    Mat detectedK = detector.detect("letters", "K");
//    Mat detectedQ = detector.detect("letters", "Q");
    return 0;
}
