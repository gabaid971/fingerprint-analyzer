#ifndef GET_CENTER_ANGLE_H
#define GET_CENTER_ANGLE_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

cv::Point find_centroid(cv::Mat src);

cv::RotatedRect get_rectangle(cv::Mat src);

cv::Mat get_image(cv::Mat src);

cv::Point find_ellipse_center(cv::Mat src);

float get_angle(cv::Mat src);

cv::Size get_size(cv::Mat src);

#endif
