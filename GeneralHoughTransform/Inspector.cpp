//
//  Inspector.cpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-24.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#include "Inspector.hpp"

void inspect(Mat image){
    Mat inspect = image.clone();
    normalize(image, inspect, 0, 1, NORM_MINMAX, CV_32F);
    imshow("inspecting", inspect);
    std::cout << "Mat Type:" << inspect.type() << std::endl;
    imwrite( "../output/inspection.jpg", inspect );
    waitKey(0);
}
