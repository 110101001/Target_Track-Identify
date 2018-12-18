/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:43
#
# Last modified: 2018-12-18 09:28
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
        int setKeyPoint(vector<KeyPoint> keypoints,Mat desc,Point p1,Point p2);
        Mat match(std::vector<KeyPoint> kp,Mat desc);
        void print();
    public:
        vector<KeyPoint> _keypoints;
        Point _Pos;
        Point _center;

        Point trackWindow1;
        Point trackWindow2;
    private:
        void KalmanInit(int x,int y);

        KalmanFilter KF;
        Mat_<float> meas;
        Mat_<float> prd;

        Mat _desc;
};


target *new_target(int x,int y);
void pop_target();
void target_track(vector<KeyPoint> kp,Mat desc,Mat &img);

#endif
