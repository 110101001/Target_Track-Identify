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
#include "surf.h"

#define ABS(x) ((x)>0?(x):-(x))

#define drawCross( center, color, d )                                        \
    line( img, Point( center.x - d, center.y - d ),                          \
    Point( center.x + d, center.y + d ), color, 1, LINE_AA, 0); \
    line( img, Point( center.x + d, center.y - d ),                          \
    Point( center.x - d, center.y + d ), color, 1, LINE_AA, 0 )

#define DIS_LIMIT 1e+5
#define WINDOW_SIZE 200

vector<target> Targets;

const Scalar colors[7]={
    Scalar(255,0,0),
    Scalar(0,255,0),
    Scalar(0,0,255),
    Scalar(255,255,0),
    Scalar(255,0,255),
    Scalar(0,255,255),
    Scalar(255,255,255),
};
static Point pointTrans(Point pt,Mat homo){
    Mat pt_mat=(Mat_<float>(3,1)<<pt.x,pt.y,1);
    Mat res=homo*pt_mat;
    return Point(res.at<float>(0,0)/res.at<float>(2,0),res.at<float>(1,0)/res.at<float>(2,0));
}

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

target *new_target(Point tw1,Point tw2){
    target nt((tw1.x+tw2.x)/2,(tw1.y+tw2.y)/2);
    nt.trackWindow1=tw1;
    nt.trackWindow2=tw2;
    if(ABS(tw1.x-tw2.x)>ABS(tw1.y-tw2.y))
        nt.target_size=ABS(tw1.x-tw2.x)/2;
    else
        nt.target_size=ABS(tw1.y-tw2.y)/2;
    Targets.push_back(nt);
    return &Targets.back();
}
void pop_target(){
    Targets.pop_back();
}

void del_target(){
    Targets.clear();
}
void target::print(){
    cout<<"Target descprition:"<<endl;
    cout<<"Position:"<<_Pos.x<<" "<<_Pos.y<<endl;
    cout<<"This target has "<<_keypoints.size()<<" points"<<endl;
}


void target_track(vector<KeyPoint> kp,Mat desc,Mat &img){ 
    for(vector<target>::iterator iter=Targets.begin();iter!=Targets.end();iter++){
        Mat tmp_desc;
        vector<KeyPoint> tmp_kp;
        Point prd=iter->KalmanPredict();
        drawCross(prd,Scalar(255,255,255),5);
        std::vector< DMatch > matches;
        tmp_kp=featuresInRange(kp,desc,
                Point(prd.x+iter->target_size+WINDOW_SIZE,prd.y+iter->target_size+WINDOW_SIZE),
                Point(prd.x-iter->target_size-WINDOW_SIZE,prd.y-iter->target_size-WINDOW_SIZE),
                tmp_desc);
        
        Mat homo=iter->match(tmp_kp,tmp_desc);
        if(homo.empty()){
            iter->_Pos=prd;
        }
        else{
            Point tw[4];
            Point *pt[1]={tw};
            int npt[1]={4};
            homo.convertTo(homo,CV_32F);
            iter->_Pos=pointTrans(iter->_center,homo);
            tw[0]=pointTrans(iter->trackWindow1,homo);
            tw[1]=pointTrans(Point(iter->trackWindow1.x,iter->trackWindow2.y),homo);
            tw[2]=pointTrans(iter->trackWindow2,homo);
            tw[3]=pointTrans(Point(iter->trackWindow2.x,iter->trackWindow1.y),homo);
            //float distance= (iter->_Pos.x-prd.x)*(iter->_Pos.x-prd.x)+(iter->_Pos.y-prd.y)*(iter->_Pos.y-prd.y);
            //if(distance>DIS_LIMIT){}
            iter->_Pos=iter->Update_pos(iter->_Pos.x,iter->_Pos.y);
            polylines(img,pt,npt,1,true,Scalar(0,0,0),1);
        }
            circle(img,iter->_Pos,10,colors[distance(Targets.begin(),iter)],2);

        //iter->print();
    }
}
