/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2018-12-17 14:25
#
# Last modified: 2018-12-18 09:17
#
# Filename:	surf.h
#
# Description: surf headers 
#
=============================================================================*/

#ifndef _SURF_H_
#define _SURF_H_

#include"target.h"

#include<opencv2/features2d.hpp>
#include"opencv2/xfeatures2d.hpp"

std::vector<KeyPoint> surf_detect(Mat src,Mat mask,Mat &desc,int hessian);
vector<KeyPoint> featuresInRange(vector<KeyPoint> keypoints,Mat desc,Point p1,Point p2,Mat &outDesc);

#endif
