/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:44
#
# Last modified:2018-12-17 16:19
#
# Filename:	main.cpp
#
# Description: entry of program
#
=============================================================================*/
#include"target.h"
#include"diff.h"
#include"surf.h"
#include<iostream>

using namespace std;

Mat display;

Point select_start;
Point select_end;

vector<KeyPoint> feature_points;
Mat desc;

void Mouse_handler(int event,int x,int y,int flags,void *ustc){
    static int  pressed=0;
    if(event==EVENT_LBUTTONDOWN){
        pressed=1;
        select_start=Point(x,y);
        select_end=Point(x,y);
    }
    else if(event==EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)){
        select_end=Point(x,y);
    }
    else if((event==EVENT_LBUTTONUP)&&(pressed==1)){
        pressed=0;
        select_end=Point(x,y);
        target *nt=new_target(select_start,select_end);
        if(!(nt->setKeyPoint(feature_points,desc,select_start,select_end))) pop_target();
        select_end=Point(0,0);
        select_start=Point(0,0);
    }
}

int main(int argc, char **argv){
    cout << "Opening camera..." << endl;
    VideoCapture capture(0); // open the first camera
    cout << "Setting camera..." << endl;
    capture.set(CAP_PROP_FRAME_WIDTH,640);
    capture.set(CAP_PROP_FRAME_HEIGHT,480);
    Mat frame,gray_frame;
    Mat mask,masked_frame;
    Mat corner;
    char c=0;
    if (!capture.isOpened())
    {
        cerr << "ERROR: Can't initialize camera capture" << endl;
        return 1;
    }
    namedWindow("frame");
    setMouseCallback("frame",Mouse_handler,0);
    capture>>frame;
    cvtColor(frame,gray_frame,COLOR_BGR2GRAY);
    Save_background(frame);
    while(c!='q'){
        capture>>frame;
        frame.copyTo(display);
        cvtColor(frame,gray_frame,COLOR_BGR2GRAY);

        if(c=='c')
            Save_background(frame);

        if(c=='d')
            del_target();
        mask=Get_mask(frame);
        //mask=Mat_<bool>::ones(480,640); 
        //corner=find_corner(gray_frame,mask);

        feature_points=surf_detect(gray_frame,mask,desc,300);
        target_track(feature_points,desc,display);
        rectangle(display,select_start,select_end,Scalar(0,255,0),2);
        imshow("frame",display);
        c=waitKey(20);
    }
    return 0;
}
