//
//  MatrixAccess.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-22.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "MatrixAccess.hpp"


void MatrixAccess::access(Mat matrix, int i, int j) {
    int pixel = (int)matrix.at<uchar>(i,j);
    cout << "pixel output at "<<i<<", "<<j<<" is:" << pixel << endl;
}

Mat MatrixAccess::copy(Mat original){
    Mat matrixCopy;
    matrixCopy.create( Size(original.cols, original.rows), CV_8UC3);
    cv::Size matrixCopySize = matrixCopy.size();
    int row = matrixCopySize.height;
    int col = matrixCopySize.width;
    cout << "row and col of copy is :" << row << " " << col << endl;
    for (int i =0 ; i<row; i++) {
        for (int j=0; j<col; j++) {
            matrixCopy.at<uchar>(i,j) = original.at<uchar>(i,j);
        }
    }
    return matrixCopy;
}
