//
//  VoteAccumulator.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-24.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "VoteAccumulator.hpp"
#include "Inspector.hpp"
using namespace std;

void copyToMap(Mat src, Mat &dst) {
    for (int i = 0; i < src.cols; i++) {
        for (int j = 0; j < src.rows; j++) {
            if (src.at<float>(j, i) > 0) {
                dst.at<uchar>(j, i) = 255;
            }
        }
    }
}

void highPass(Mat src, Mat &dst, float portion) {
    float max = 0;
    float min = 0;
    for (int i = 0; i < src.cols; i++) {
        for (int j = 0; j < src.rows; j++) {
            float val = src.at<float>(j, i);
            if ( val < min ) {
                min = val;
            } else if (val > max) {
                max = val;
            }
        }
    }
    float cutoff = (max - min) * portion + min;
    for (int i = 0; i < src.cols; i++) {
        for (int j = 0; j < src.rows; j++) {
            float val = src.at<float>(j, i);
            if ( val > cutoff ) {
                dst.at<float>(j,i) = val;
            } else {
                dst.at<float>(j,i) = 0;
            }
        }
    }
}
Mat VoteAccumulator::accumulate(Mat edgeMat, Mat phiMat, Rtable table) {
    Mat inspection = Mat(edgeMat.rows, edgeMat.cols, CV_32F, cvScalar(0));
    //for each edge point in edgeMat
    for (int i=0; i<edgeMat.cols; ++i) {
        for (int j=0; j<edgeMat.rows; ++j) {
            if ( (int) edgeMat.at<uchar>(j,i) == 255  ) {
                //determine its angle
                float angle = (float) phiMat.at<float>(j,i);
                //find the bin for the angle
                float divisor = 360 / (float)intervals;
                int bin = cvRound(angle / divisor) % intervals;
                
                for (int wiggle = wiggleMin; wiggle <= wiggleMax; wiggle += divisor) {
                    int binOffset = wiggle / divisor;
                    int newBin = ( bin + binOffset + intervals ) % intervals;
                    int scaleSteps = ( maxScale - 1 ) / scaleStep;
                    for (int s = 0; s < scaleSteps; s++) {
                        float scale = 1 + s * scaleStep;
                        for (int k = 0; k < table[newBin].size(); k++) {
                            int scaledDeltaY = cvRound((float)table[newBin][k](0) * scale);
                            int scaledDeltaX = cvRound((float)table[newBin][k](1) * scale);
                            
                            inspection.at<float>(j - scaledDeltaY,i - scaledDeltaX) += 1;
                        }
                    }
                }
                
                
            }
            
        }
    }
    blur(inspection, inspection, Size(11,11));
//    medianBlur(inspection, inspection, 5);
    highPass(inspection, inspection, 0.85);
    inspect(inspection);
    
    
    return inspection;
}
