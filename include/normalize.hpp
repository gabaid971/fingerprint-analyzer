#ifndef NORMALIZE_H
#define NORMALIZE_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

float mean_grey(cv::Mat src);

float var_grey(cv::Mat src);

cv::Mat normalize(cv::Mat src, float mean, float var);

#endif
