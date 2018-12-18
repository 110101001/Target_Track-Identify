/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2018-12-17 14:24
#
# Last modified: 2018-12-18 09:49
#
# Filename:	surf.cpp
#
# Description: Surf feature functions
#
=============================================================================*/

#include"surf.h"
#include"target.h"
#include<iostream>

using namespace cv;
using namespace cv::xfeatures2d;

std::vector<KeyPoint> surf_detect(Mat src,Mat mask,Mat &desc,int hessian){
    Ptr<SURF> detector = SURF::create( hessian  );
    std::vector<KeyPoint> keypoints;
    detector->detectAndCompute( src, mask,keypoints,desc);
    return keypoints;
}

void target::setKeyPoint(vector<KeyPoint> keypoints,Mat desc,Point p1,Point p2){
    for(vector<KeyPoint>::iterator iter=keypoints.begin();iter!=keypoints.end();iter++){
        if(IN_RANGE(iter->pt.x,p1.x,p2.x)&&IN_RANGE(iter->pt.y,p1.y,p2.y)){
            _keypoints.push_back(*iter);
            int row=distance(keypoints.begin(),iter);
            if(_desc.empty()){
                _desc=desc.row(row).clone();
            }
            else{
                _desc.push_back(desc.row(row));
            }
        }
    }
    print();
}

std::vector<DMatch> target::match(std::vector<KeyPoint> kp,Mat desc){
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector< DMatch > matches;
    matcher->match( _desc, desc, matches  );
    return matches;
}
