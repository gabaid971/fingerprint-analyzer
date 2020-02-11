#ifndef TRANSLATION_X_H
#define TRANSLATION_X_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int best_translation(cv::Mat src, cv::Mat obj);

float translation_min_error(cv::Mat src, cv::Mat obj);

float translation_max_error(cv::Mat src, cv::Mat obj);

void draw_translation(cv::Mat src, cv::Mat obj, cv::Mat draw);

#endif
