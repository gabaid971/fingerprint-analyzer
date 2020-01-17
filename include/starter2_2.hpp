#ifndef STARTER2_2_H
#define STARTER2_2_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;

cv::Mat get_angle(cv::Mat src, cv::Mat dst, cv::Mat thr, cv::Mat final);


#endif
