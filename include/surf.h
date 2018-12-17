/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2018-12-17 14:25
#
# Last modified:2018-12-17 16:19
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

std::vector<KeyPoint> surf_detect(Mat src,Mat mask,int hessian);

#endif
