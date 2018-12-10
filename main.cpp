/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time: 2018-12-10 10:44
#
# Last modified: 2018-12-10 10:44
#
# Filename: main.c
#
# Description: entry of program
#
=============================================================================*/
#include"target.h"

int main(int argc, char **argv){
    target a(100,100);
    a.KalmanPredict();
    return 0;
}
