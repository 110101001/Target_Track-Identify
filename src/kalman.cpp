/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:23
#
# Last modified: 2018-12-17 20:08
#
# Filename:	kalman.cpp
#
# Description: Use kalman to predict targets' movement. 
#
=============================================================================*/
#include "target.h"
#include "math.h"
#include <iostream>


#define ABS(x) ((x)>0?(x):-(x))


#define PROCESS_ERR 1e-5
#define MEAS_ERR 1e-3
#define POST_ERR 1e-5 

using namespace cv;

void target::KalmanInit(int x,int y){
    KF.statePre.setTo(0);
    KF.statePre.at<float>(0,0)=x;
    KF.statePre.at<float>(1,0)=y;
    KF.statePost.setTo(0);
    KF.statePost.at<float>(0,0)=x;
    KF.statePost.at<float>(1,0)=y;

    KF.transitionMatrix = (Mat_<float>(4,4)<<1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1);
    setIdentity(KF.processNoiseCov, Scalar::all(PROCESS_ERR)); 
    setIdentity(KF.measurementMatrix, Scalar::all(1)); //adjust this for faster convergence - but higher noise
    setIdentity(KF.measurementNoiseCov, Scalar::all(MEAS_ERR));
    setIdentity(KF.errorCovPost, Scalar::all(POST_ERR));
    meas=Mat_<float>::zeros(2,1);
}


Point target::KalmanPredict(){
    prd=KF.predict();
    return Point(prd.at<float>(0,0),prd.at<float>(1,0));
}

Point target::Update_pos(int x,int y){
    meas.at<float>(0,0)=x;
    meas.at<float>(1,0)=y;
    Mat state=KF.correct(meas);
    _Pos.x=state.at<float>(0,0);
    _Pos.y=state.at<float>(1,0);
    return _Pos;
}
