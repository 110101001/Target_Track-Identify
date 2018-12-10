/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:43
#
# Last modified: 2018-12-10 10:43
#
# Filename: target.h
#
# Description: define class target 
#
=============================================================================*/
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

class target{
    public:
        target();
        target(int x, int y);

        Point KalmanPredict();
        Point Update_pos(int x,int y);

    private:
        void KalmanInit(int x,int y);

        Point _Pos;
        KalmanFilter KF;
        Mat_<float> meas;
        Mat_<float> prd;
};
