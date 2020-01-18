#ifndef ERROR_H
#define ERROR_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

float err(cv::Mat diff);

#endif
