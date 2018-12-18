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
    _Pos=Point(x,y);
    meas=Mat_<float>(2,1);
    prd=Mat_<float>(4,1);
    KF=KalmanFilter(4,2,0);

    KalmanInit(x,y);
}

target *new_target(int x,int y){
    target nt(x,y);
    Targets.push_back(nt);
    return &Targets.back();
}

void target::print(){
    cout<<"Target descprition:"<<endl;
    cout<<"Position:"<<_Pos.x<<" "<<_Pos.y<<endl;
    cout<<"This target has "<<_keypoints.size()<<" points"<<endl;
}


void target_track(vector<KeyPoint> kp,Mat desc,Mat img){ 
    for(vector<target>::iterator iter=Targets.begin();iter!=Targets.end();iter++){
        std::vector< DMatch > matches;
        matches=iter->match(kp,desc);

    }
}
