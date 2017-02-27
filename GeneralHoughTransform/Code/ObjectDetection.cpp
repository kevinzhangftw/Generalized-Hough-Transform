//
//  ObjectDetection.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-17.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "ObjectDetection.hpp"
#include "Inspector.hpp"
static Mat loadImage(const String& name){
    Mat image = imread(name, IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cerr << "Can't load image - " << name << std::endl;
        exit(-1);
    }
    return image;
}

Mat overlay(Mat &graySource, Mat accumulation) {
    Mat copy = graySource.clone();
    for (int i = 0; i < graySource.cols; i++) {
        for (int j = 0; j < graySource.rows; j++) {
            if (accumulation.at<float>(j,i) > 0) {
                circle(copy, Point(i,j),50, Scalar(0,0,255),0, 6,0);
            }
        }
    }
    return copy;
}

Mat ObjectDetection::detect(String source, String object) {
    
    
    Mat grayObject = grayScaleOf(object);
    TableGenerator tabler = TableGenerator();
    Mat graySource = grayScaleOf(source);
    medianBlur(graySource, graySource, 5);
    Mat sourceEdge = tabler.detectEdges(graySource);
    Mat sourcePhiMat = tabler.phiMat(graySource);
    
//    inspect(grayObject);
//    inspect(graySource);
//    inspect(sourceEdge);
//    inspect(sourcePhiMat);
    
    Rtable rTable = tabler.generate(grayObject);
    tabler.inspectTable(rTable);
    VoteAccumulator acc = VoteAccumulator();
    Mat accumulation = acc.accumulate(sourceEdge, sourcePhiMat, rTable); //uchar
    inspect(accumulation);
    Mat overlaid = overlay(graySource, accumulation);
    /*
     
     Vec2i objectPosition = detectObject(bear, ghtModel);
     Mat detectedImage = putCircleIntoAt(source, objectPosition);

     */
    inspect(overlaid);
    
    return graySource;
}


Mat ObjectDetection::grayScaleOf(String object) {
    Mat objectMat;
    if (object == "bear") {
        objectMat = imread("template_bear.png", 1);
    } else if (object == "elephant") {
        objectMat = imread("template_elephant.png", 1);
    } else if (object == "Q") {
        objectMat = imread("template_Q.png", 1);
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
    }else if (object == "letters") {
        return loadImage("letters.png");
    }
    Mat tempMat;
    
    cvtColor(objectMat, tempMat, CV_BGR2GRAY);
//    Mat edgeImage = detectEdges(tempMat);
    return tempMat;
}
