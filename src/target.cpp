/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:43
#
# Last modified: 2018-12-17 20:04
#
# Filename:	target.cpp
#
# Description: target's function 
#
=============================================================================*/

#include "target.h"

vector<target> Targets;

target::target(){
    _Pos=Point(0,0);
    meas=Mat_<float>(2,1);
    prd=Mat_<float>(4,1);
    KF=KalmanFilter(4,2,0);

    KalmanInit(0,0);
}

target::target(int x,int y){
    _Pos=Point(0,0);
    meas=Mat_<float>(2,1);
    prd=Mat_<float>(4,1);
    KF=KalmanFilter(4,2,0);

    KalmanInit(x,y);
}

void target::SetKeyPoint(vector<KeyPoint> keypoints,Point p1,Point p2){
    for(vector<KeyPoint>::iterator iter=keypoints.begin();iter!=keypoints.end();iter++){
        if(IN_RANGE(iter->pt.x,p1.x,p2.x)&&IN_RANGE(iter->pt.y,p1.y,p2.y)){
            _keypoints.push_back(*iter);
        }
    }
}

target *new_target(){
    target nt;
    Targets.push_back(nt);
    return &Targets.back();
}
