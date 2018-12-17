/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 18:35
#
# Last modified:2018-12-11 10:03
#
# Filename:	diff.cpp
#
# Description: background spltrential method
#
=============================================================================*/
#include "diff.h"
#include <iostream>

#define ABS(x) ((x)>0?(x):-(x))

#define MOVE_TH 50
#define KSIZE Size(5,5)
#define MASK_THRESH 80
using namespace std;
using namespace cv;

Mat background;

Mat Last_frame;

void Save_background(Mat bg){
    bg.copyTo(background);
    bg.copyTo(Last_frame);
    return;
}

Mat Get_mask(Mat present){

    Mat diff;
    Mat_<bool> ele(5,5);
    Mat splt[3];
    Mat_<bool> mask;
    
    ele<<0,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,0,1,0,0;

    absdiff(present,background,diff);
    split(diff,splt);
    splt[0]=abs(splt[0])+abs(splt[1])+abs(splt[2]);
    threshold(splt[0],mask,MASK_THRESH,255,THRESH_BINARY_INV);
    erode(mask,mask,ele);
    dilate(mask,mask,ele);
    dilate(mask,mask,ele);
    erode(mask,mask,ele);
    imshow("splt",mask);

    return ~mask;
}
