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

using namespace cv;
using namespace std;

void runGHT(char c){
    //c = 't'; // create template
    //c = 'r'; // run algorithm
    if (c == 't'){
        GenHoughTrnf ght;
        ght.createTemplate();
    }
    else if (c == 'r'){
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
    // insert code here...
//    cout<< "CV_VERSION: " << CV_VERSION << endl;
//    char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below
//    printf("Current dir: %s", dir);
//    
//    Mat src = imread("animals.jpg", CV_LOAD_IMAGE_COLOR);
//    imshow("Animals gone BEASTTT!!!", src);
//    waitKey(0);
    runGHT('t');
    
    runGHT('r');
    return 0;
}
