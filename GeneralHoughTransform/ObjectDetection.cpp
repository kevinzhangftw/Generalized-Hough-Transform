//
//  ObjectDetection.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-17.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "ObjectDetection.hpp"

Mat ObjectDetection::detect(String source, String object) {
    Mat objectEdges = edgesOf(object);
    TableGenerator tabler = TableGenerator();
    Rtable rTable = tabler.generate(objectEdges);
    //TODO:
    //     Rtable ghtModel = generateTable(objectEdges);
    //
    Mat sourceMat;
    if (source == "animals") {
        sourceMat = imread("animals.jpg", 0);
    } else if (source == "letters") {
        sourceMat = imread("letters.jpg", 0);
    }
    
    /*
     
     Vec2i objectPosition = detectObject(bear, ghtModel);
     Mat detectedImage = putCircleIntoAt(source, objectPosition);

     */
    
    
    return objectEdges;
}


Mat ObjectDetection::edgesOf(String object) {
    Mat objectMat;
    if (object == "bear") {
        objectMat = imread("template_bear.png", 1);
    } else if (object == "elephant") {
        
    } else if (object == "Q") {
        
    } else if (object == "K") {
        
    }
    Mat tempMat;
    cvtColor(objectMat, tempMat, CV_BGR2GRAY);
    Mat edgeImage = detectEdges(tempMat);
    return edgeImage;
}

Mat ObjectDetection::detectEdges(Mat source) {
    Mat edgeMat;
    blur( source, edgeMat, Size(3,3) );
    int thr1 = 1, thr2 = 100;
    Canny( edgeMat, edgeMat, thr1, thr2, 3 );
    return edgeMat;
}
