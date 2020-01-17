#ifndef STARTER2_2_H
#define STARTER2_2_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>


float h0(float t);
float h1(float t);
float h2(float t);
float h3(float t);
float cubic_spline( cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4, float x);
uchar calculate_pixel_value( int x, int y, float theta, cv::Point center, cv::Mat src);
void fill_dst(float theta, cv::Point center, cv::Mat src, cv::Mat dst);
int err(cv::Mat diff);
cv::Point find_centroid(cv::Mat src);

#endif
