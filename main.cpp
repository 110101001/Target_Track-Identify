/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:44
#
# Last modified:2018-12-10 18:59
#
# Filename:	main.cpp
#
# Description: entry of program
#
=============================================================================*/
#include"target.h"
#include"diff.h"
#include"harris.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv){
    Mat frame,gray_frame;
    Mat mask,masked_frame;
    Mat corner;
    char c=0;
    cout << "Opening camera..." << endl;
    VideoCapture capture(0); // open the first camera
    if (!capture.isOpened())
    {
        cerr << "ERROR: Can't initialize camera capture" << endl;
        return 1;
    }
    capture>>frame;
    cvtColor(frame,gray_frame,CV_BGR2GRAY);
    Save_background(frame);
    while(c!='q'){
        capture>>frame;
        cvtColor(frame,gray_frame,CV_BGR2GRAY);

        if(c=='c')
            Save_background(frame);

        mask=Get_mask(frame);
        //gray_frame.setTo(0,mask);

        corner=find_corner(gray_frame,mask);

        imshow("frame",gray_frame);
        c=waitKey(10);
    }
    return 0;
}
