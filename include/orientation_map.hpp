#ifndef ORIENTATION_MAP_H
#define ORIENTATION_MAP_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


Mat get_orientation_map(Mat src, int block_size);

#endif
