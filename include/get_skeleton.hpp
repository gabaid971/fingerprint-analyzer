#ifndef GET_SKELETON_H
#define GET_SKELETON_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

bool ctb(cv::Mat src, int i, int j );

bool check_1(cv::Mat src, int i, int j );

bool check_2(cv::Mat src, int i, int j );

bool check_3(cv::Mat src, int i, int j );

std::vector<cv::Point> step(cv::Mat src, bool state, std::vector<Point> to_erase);

cv::Mat get_skeleton(cv::Mat src);

#endif
