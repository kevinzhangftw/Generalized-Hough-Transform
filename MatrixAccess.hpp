//
//  MatrixAccess.hpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-22.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#ifndef MatrixAccess_hpp
#define MatrixAccess_hpp

#include <stdio.h>
#include <iostream>
#include "stdlib.h"
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <thread>
#include <string>

using namespace cv;
using namespace std;

class MatrixAccess {
    
public:
    void access(String);
    void copy(Mat);
    
};


#endif /* MatrixAccess_hpp */
