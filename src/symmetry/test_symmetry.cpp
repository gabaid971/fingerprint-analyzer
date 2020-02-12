/*!
 * \file test_symmetry.cpp
 * \brief Simple symmetry of an image with the open cv function "remap"
 * \author Daniel Gabaï
 */
#include "update_symmetry.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{  /* use of the opencv function remap to make the symmetry of a picture
  we will reimplement remap later for the rotation*/
  cv::Mat src, dst;
  cv::Mat map_x, map_y;
  const char* remap_window = "symmetry";
  src = imread( "images/papillon.jpg", IMREAD_GRAYSCALE );
  dst.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  namedWindow( remap_window, WINDOW_AUTOSIZE );

  update_map_symmetry(map_x, map_y);
  remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(255) );
  // Display results
  imshow( remap_window, src );
  waitKey(0);
  return 0;
}
