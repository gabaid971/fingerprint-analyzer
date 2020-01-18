#ifndef UPDATE_ROTATION_H
#define UPDATE_ROTATION_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

void update_map_rotation(cv::Mat map_x, cv::Mat map_y, cv::Point center, float theta);

#endif
