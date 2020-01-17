#ifndef STARTER2_1_H
#define STARTER2_1_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

void update_map_rotation(float theta, cv::Point center, cv::Mat map_x, cv::Mat map_y);

int err(cv::Mat diff);

cv::Point find_centroid(cv::Mat src);

#endif
