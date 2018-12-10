/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:43
#
# Last modified: 2018-12-10 10:43
#
# Filename: target.cpp
#
# Description: target's member function 
#
=============================================================================*/

#include "target.h"

target::target(){
    _pos=Point(0,0);
    meas=Mat_<float>(2,1);
    prd=Mat_<float>(4,1);
    KF=KalmanFilter(4,2,0);
    KalmanInit(0,0);
}

target::target(int x,int y){
    _pos=Point(0,0);
    meas=Mat_<float>(2,1);
    prd=Mat_<float>(4,1);
    KF=KalmanFilter(4,2,0);
    KalmanInit(x,y);
}


