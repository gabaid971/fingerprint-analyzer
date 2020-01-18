#ifndef ERROR_H
#define ERROR_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

float err(cv::Mat diff);

float best_translation(cv::Mat src, cv::Mat obj);

float translation_min_error(cv::Mat src, cv::Mat obj);

float translation_max_error(cv::Mat src, cv::Mat obj);

void draw_translation(cv::Mat src, cv::Mat obj, cv::Mat draw);

#endif
