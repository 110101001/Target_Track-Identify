/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:43
#
# Last modified: 2018-12-18 15:26
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
    _center=Point(0,0);
    meas=Mat_<float>(2,1);
    prd=Mat_<float>(4,1);
    KF=KalmanFilter(4,2,0);

    KalmanInit(0,0);
}

target::target(int x,int y){
    _Pos=Point(x,y);
    _center=Point(x,y);
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
void pop_target(){
    Targets.pop_back();
}

void target::print(){
    cout<<"Target descprition:"<<endl;
    cout<<"Position:"<<_Pos.x<<" "<<_Pos.y<<endl;
    cout<<"This target has "<<_keypoints.size()<<" points"<<endl;
}


void target_track(vector<KeyPoint> kp,Mat desc,Mat &img){ 
    for(vector<target>::iterator iter=Targets.begin();iter!=Targets.end();iter++){
        Point prd=iter->KalmanPredict();
        circle(img,prd,10,Scalar(255,0,0),2);
        std::vector< DMatch > matches;
        Mat_<float> center=(Mat_<float>(3,1)<<(iter->_center.x),(iter->_center.y),1);
        Mat pos;
        Mat homo=iter->match(kp,desc);
        if(homo.empty()) continue;
        homo.convertTo(homo,CV_32F);
        pos=homo*center;
        iter->_Pos.x=pos.at<float>(0,0)/pos.at<float>(2,0);
        iter->_Pos.y=pos.at<float>(1,0)/pos.at<float>(2,0);
        iter->_Pos=iter->Update_pos(iter->_Pos.x,iter->_Pos.y);
        circle(img,iter->_Pos,10,Scalar(255,255,0),2);

        //iter->print();
    }
}
