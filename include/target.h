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

class target{
    public:
        target();
        target(int x, int y);

        void KalmanInit(int x,int y);
        void KalmanPredict(int x,int y);

    private:
        Point _Pos;
        KalmanFilter KF(4,2,0);
        Mat_<float> meas(2,1);
        Mat_<float> prd(4,1);
};
