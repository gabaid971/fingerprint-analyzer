/*!
 * \file test_orientation_map.cpp
 * \brief Starting from a fingerprint image, we got its orientation map
 * \author Daniel Gabaï
 */
#include "orientation_map.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{
  Mat src;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  // Show input image
  imshow( "Input image", src );
  waitKey(0);
  Mat ori_map = get_orientation_map(src, 8);
  // Display results
  imshow( "Orientation map", ori_map );
  waitKey(0);
  return 0;
}
