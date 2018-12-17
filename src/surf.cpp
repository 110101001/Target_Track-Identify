/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2018-12-17 14:24
#
# Last modified:2018-12-17 16:19
#
# Filename:	surf.cpp
#
# Description: Surf feature functions
#
=============================================================================*/

#include"surf.h"
#include<iostream>

using namespace cv;
using namespace cv::xfeatures2d;

std::vector<KeyPoint> surf_detect(Mat src,Mat mask,int hessian){
    Ptr<SURF> detector = SURF::create( hessian  );
    std::vector<KeyPoint> keypoints;
    detector->detect( src, keypoints,mask);
    return keypoints;
}
