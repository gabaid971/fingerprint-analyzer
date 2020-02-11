/*!
 * \file test_minutiae.cpp
 * \brief Starting from an enhancement fingerprint image,
we will find minutiae as bifurcation points and ending points.
 * \author Daniel Gabaï
 */
#include "minutiae.hpp"
#include "get_skeleton.hpp"

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
  src = imread( "images/after_enhancement.png", IMREAD_GRAYSCALE );
  threshold(src, src, 127, 255, THRESH_BINARY);
  // Show the input image after the threshold
  imshow( "Input image", src );
  waitKey(0);
  // Thinning of the thresholded image
  src = get_skeleton(src);
  // Ending points have a crossing number of 1
  Mat ending_points = find_minutiae(src, 1);
  // Bifurcation points have a crossing number of 3
  Mat bifurcation_points = find_minutiae(src, 3);
  // Display results
  imshow( "Ending points", ending_points );
  waitKey(0);
  imshow( "Bifurcation points", bifurcation_points );
  waitKey(0);
  return 0;
}
