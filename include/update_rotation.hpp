#ifndef UPDATE_ROTATION_H
#define UPDATE_ROTATION_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

void update_map_rotation(float theta, cv::Point center, cv::Mat map_x, cv::Mat map_y);

#endif
