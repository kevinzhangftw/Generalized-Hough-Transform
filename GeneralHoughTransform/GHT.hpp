//
//  GHT.hpp
//  GeneralHoughTransform
//
//  Created by Kai Zhang on 2017-02-11.
//  Copyright © 2017 Kai Zhang. All rights reserved.
//

#ifndef GHT_hpp
#define GHT_hpp

#include <stdio.h>

struct Rpoint{
    int dx;
    int dy;
    float phi;
};

struct Rpoint2{
    float x;
    float y;
    int phiindex;
};

#endif /* GHT_hpp */
