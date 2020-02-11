/*!
 * \file test_get_center_angle.cpp
 * \brief Starting from a fingerprint image,
we will find the center of the shape and the angle
of the ellipse which fits the best to the shape.
 * \author Daniel Gabaï
 */
#include "get_center_angle.hpp"

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
  // Show the input image
  src = imread( "images/rotated_image.png", IMREAD_GRAYSCALE );
  imshow( "Input image", src );
  waitKey(0);
  Mat final = get_image(src);
  float angle = get_angle(src);
  Point ellipse_center = find_ellipse_center(src);
  Point centroid = find_centroid(src);
  // Display results
  imshow( "Angle and center", final );
  waitKey(0);
  cout << "The centroid is: " << centroid << endl;
  cout << "The center of the ellipse is: " << ellipse_center << endl;
  cout << "The angle of the ellipse is: " << angle << endl;
  return 0;
}
