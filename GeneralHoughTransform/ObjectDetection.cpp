//
//  ObjectDetection.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-17.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "ObjectDetection.hpp"

static Mat loadImage(const String& name)
{
    Mat image = imread(name, IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cerr << "Can't load image - " << name << std::endl;
        exit(-1);
    }
    return image;
}

Mat ObjectDetection::detect(String source, String object) {
    
    
    Mat grayObject = grayScaleOf(object);
    TableGenerator tabler = TableGenerator();
    Mat graySource = grayScaleOf(source);
    medianBlur(graySource, graySource, 5);
    Mat sourceEdge = tabler.detectEdges(graySource);
    Mat sourcePhiMat = tabler.phiMat(graySource);
    Rtable rTable = tabler.generate(grayObject);
    //TODO:
    //     Rtable ghtModel = generateTable(objectEdges);
    //

    /*
     
     Vec2i objectPosition = detectObject(bear, ghtModel);
     Mat detectedImage = putCircleIntoAt(source, objectPosition);

     */
    
    
    return grayObject;
}


Mat ObjectDetection::grayScaleOf(String object) {
    Mat objectMat;
    if (object == "bear") {
        objectMat = imread("template_bear.png", 1);
    } else if (object == "elephant") {
        
    } else if (object == "Q") {
        
    } else if (object == "K") {
        objectMat = imread("template_K.png", 1);
    } else if (object == "block") {
        return loadImage("block.tif");
    } else if (object == "animals") {
        objectMat = imread("animals.jpg");
    } else if (object == "blockelement") {
        return loadImage("blockelement.png");
    }else if (object == "blockscience") {
        return loadImage("blockscience.png");
    }
    Mat tempMat;
    
    cvtColor(objectMat, tempMat, CV_BGR2GRAY);
//    Mat edgeImage = detectEdges(tempMat);
    return tempMat;
}
