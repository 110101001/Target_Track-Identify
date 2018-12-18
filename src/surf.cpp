/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2018-12-17 14:24
#
# Last modified: 2018-12-18 09:49
#
# Filename:	surf.cpp
#
# Description: Surf feature functions
#
=============================================================================*/

#include"surf.h"
#include"target.h"
#include<iostream>

using namespace cv;
using namespace cv::xfeatures2d;

std::vector<KeyPoint> surf_detect(Mat src,Mat mask,Mat &desc,int hessian){
    Ptr<SURF> detector = SURF::create( hessian  );
    std::vector<KeyPoint> keypoints;
    detector->detectAndCompute( src, mask,keypoints,desc);
    return keypoints;
}

int target::setKeyPoint(vector<KeyPoint> keypoints,Mat desc,Point p1,Point p2){
    for(vector<KeyPoint>::iterator iter=keypoints.begin();iter!=keypoints.end();iter++){
        if(IN_RANGE(iter->pt.x,p1.x,p2.x)&&IN_RANGE(iter->pt.y,p1.y,p2.y)){
            _keypoints.push_back(*iter);
            int row=distance(keypoints.begin(),iter);
            if(_desc.empty()){
                _desc=desc.row(row).clone();
            }
            else{
                _desc.push_back(desc.row(row));
            }
        }
    }
    print();
    return _keypoints.size();
}

Mat target::match(std::vector<KeyPoint> kp,Mat desc){
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector< DMatch > matches;
    matcher->match( _desc, desc, matches  );
    int match_num =  matches.size();
    Mat po(match_num, 2, CV_32F);
    Mat ps(match_num, 2, CV_32F);
    //Mat good_po;
    //Mat good_ps;
    Point2f pt;
    for (int i=0; i<match_num; i++) {
        pt = _keypoints[matches[i].queryIdx].pt;
        po.at<float>(i, 0) = pt.x;
        po.at<float>(i, 1) = pt.y;

        pt = kp[matches[i].trainIdx].pt;
        ps.at<float>(i, 0) = pt.x;
        ps.at<float>(i, 1) = pt.y;
    }
    Mat homo=findHomography(po,ps,RANSAC);
    /*vector<bool> RANSAC_mask;
    findFundamentalMat(po, ps, FM_RANSAC,3,0.99,RANSAC_mask);    

    for (int i=0; i<match_num; i++) {
        if(RANSAC_mask[i]!=0){
            if(good_po.empty()){
                good_po=po.row(i).clone();
                good_ps=ps.row(i).clone();
            }
            else{
                good_po.push_back(po.row(i));
                good_ps.push_back(ps.row(i));
            }
        }
    }*/
    return homo;
}
