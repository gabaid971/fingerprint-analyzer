#ifndef MINUTIAE_H
#define MINUTIAE_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int crossing_number(cv::Mat src, int i, int j);

cv::Mat find_minutiae(cv::Mat src, int value);

#endif
