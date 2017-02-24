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
    Mat sourceMat;
    if (source == "animals") {
        sourceMat = loadImage("animals.jpg");
    } else if (source == "letters") {
        sourceMat = loadImage("letters.jpg");
    } else if (source == "block") {
        sourceMat = loadImage("block.tif");
    }
    Mat objectMat;
    if (object == "bear") {
        objectMat = imread("template_bear.png", 1);
    } else if (object == "elephant") {
        
    } else if (object == "Q") {
        
    } else if (object == "K") {
        
    } else if (object == "block") {
        objectMat = loadImage("block.tif");
    }
    
    Mat grayObject = grayScaleOf(object);
    TableGenerator tabler = TableGenerator();
    Rtable rTable = tabler.generate(grayObject);
    //TODO:
    //     Rtable ghtModel = generateTable(objectEdges);
    //

    tabler.inspect(sourceMat);
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
        
    } else if (object == "block") {
        return loadImage("block.tif");
    }
    Mat tempMat;
    
    cvtColor(objectMat, tempMat, CV_BGR2GRAY);
//    Mat edgeImage = detectEdges(tempMat);
    return tempMat;
}
