/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 16:10
#
# Last modified:2018-12-11 10:54
#
# Filename:	harris.cpp
#
# Description: Harris corner dectecter 
#
=============================================================================*/
#include "target.h"

#define BLK_SIZE 2
#define AP_SIZE 3
#define K_P 0.04
#define CORNER_TRESH 7e-4

Mat find_corner(Mat img,Mat mask){
    Mat corner;
    Mat dilated;
    Mat show;
    Mat_<bool> dele(5,5);
    Mat_<bool> mele(6,6);
    dele.setTo(1);
    mele.setTo(1);
    cornerHarris(img, corner, BLK_SIZE,AP_SIZE, K_P);
    corner=abs(corner);
    dilate(corner,dilated,dele);
    dilate(mask,mask,mele);
    compare(corner,dilated,dilated,CMP_NE);
    corner.setTo(0,mask);
    //normalize( corner, show, 0, 255, NORM_MINMAX, CV_8UC1, Mat() );
    //imshow("cor",show);

    for( int i = 0; i < corner.rows ; i++  )
    {
        for( int j = 0; j < corner.cols; j++  )
        {
            if( corner.at<float>(i,j) > CORNER_TRESH  )
            {
                circle( img, Point(j,i), 5,  Scalar(255), 2, 8, 0  );
            }

        }

    }

    return corner;
}


