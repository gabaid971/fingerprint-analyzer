#ifndef FINGER_PRESSURE_H
#define FINGER_PRESSURE_H


#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;

double distance_to(cv::Point p1, cv::Point p2);

double c(double x, double y);

uchar new_pixel(int i, int j, cv::Point center, cv::Mat trans);

#endif
