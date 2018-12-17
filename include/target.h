/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:43
#
# Last modified: 2018-12-17 19:37
#
# Filename:	target.h
#
# Description: define class target 
#
=============================================================================*/
#ifndef _TARGET_H_
#define _TARGET_H_
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/video/tracking.hpp"


#define IN_RANGE(x,l1,l2) ((x)<=((l1)>(l2)?(l1):(l2))&&(x)>=((l1)>(l2)?(l2):(l1)))

using namespace cv;
using namespace std;

class target{
    public:
        target();
        target(int x, int y);

        Point KalmanPredict();
        Point Update_pos(int x,int y);
        void SetKeyPoint(vector<KeyPoint> keypoints,Point p1,Point p2);

    private:
        void KalmanInit(int x,int y);

        Point _Pos;
        KalmanFilter KF;
        Mat_<float> meas;
        Mat_<float> prd;

        vector<KeyPoint> _keypoints;
};


target *new_target();

#endif
