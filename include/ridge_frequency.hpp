#ifndef RIDGE_FREQUENCY_H
#define RIDGE_FREQUENCY_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

cv::Mat get_orientation_block(cv::Mat src, int block_size);

std::vector<float> x_signature(cv::Mat src, int i, int j, int block_size);

std::vector<float> deriv_signature(std::vector<float>& x_signature);

std::vector<float> second_deriv_signature(std::vector<float>& deriv_signature);

float frequency(std::vector<float>& x_signature);

#endif
