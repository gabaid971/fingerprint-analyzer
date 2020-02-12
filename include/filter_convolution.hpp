#ifndef FILTER_CONVOLUTION_H
#define FILTER_CONVOLUTION_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void flip(cv::Mat& kernel);

void padding(cv::Mat &image, cv::Mat kernel);

void convolution_2D(cv::Mat image, cv::Mat kernel, std::string name);

void DFT(cv::Mat& image, cv::Mat& kernel);

void inverse(cv::Mat image, cv::Mat kernel, cv::Mat save);

void diff(cv::Mat mt, cv::Mat mt1);

#endif
