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

void Mouse_handler(int event,int x,int y,int flags,void *ustc){
    static int  pressed=0;
    if(event==EVENT_LBUTTONDOWN){
        pressed=1;
        select_start=Point(x,y);
    }
    else if(event==EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)){
        select_end=Point(x,y);
    }
    else if((event==EVENT_LBUTTONUP)&&(pressed==1)){
        pressed=0;
        select_end=Point(x,y);
        target *nt=new_target();
        nt->SetKeyPoint(feature_points,select_start,select_end);

        select_end=Point(0,0);
        select_start=Point(0,0);
        cout<<select_start.x<<" "<<select_start.y<<" to "<<x<<" "<<y<<endl;
    }
}

int main(int argc, char **argv){
    Mat frame,gray_frame;
    Mat mask,masked_frame;
    Mat corner;
    char c=0;
    cout << "Opening camera..." << endl;
    VideoCapture capture(0); // open the first camera
    capture.set(CAP_PROP_FRAME_WIDTH,640);
    capture.set(CAP_PROP_FRAME_HEIGHT,480);
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
        cvtColor(frame,gray_frame,COLOR_BGR2GRAY);

        if(c=='c')
            Save_background(frame);

        mask=Get_mask(frame);

        //corner=find_corner(gray_frame,mask);

        feature_points=surf_detect(gray_frame,mask,100);
        drawKeypoints( frame, feature_points, display );
        rectangle(display,select_start,select_end,Scalar(255,0,0),2);
        imshow("frame",display);
        c=waitKey(30);
    }
    return 0;
}
