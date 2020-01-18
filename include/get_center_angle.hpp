#ifndef GET_CENTER_ANGLE_H
#define GET_CENTER_ANGLE_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;


cv::Point find_centroid(cv::Mat src);
cv::Mat get_angle(cv::Mat src, cv::Mat dst, cv::Mat thr, cv::Mat final);


#endif
