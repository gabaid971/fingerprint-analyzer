#ifndef FILTER_CONVOLUTIONFFT_H
#define FILTER_CONVOLUTIONFFT_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void DFT(cv::Mat& image, cv::Mat& kernel);

void inverse(cv::Mat image, cv::Mat kernel, cv::Mat save);

#endif
