/*!
 * \file test_remap.cpp
 * \brief Test of the reimplementation of the remap function for the rotation
 * \author Daniel Gabaï
 */
#include "remap.hpp"
#include "error.hpp"
#include "get_center_angle.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>
#include <time.h>

using namespace cv;
using namespace std;

int main()
{
  // Initialization of the time counter
  int time = 0;
  Mat src;
  src = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE );
  // Center of rotation
  Point centroid = find_centroid( src );
  // Angle of rotation
  float theta =  0.68912 ;
  Mat dst;
  cout << "Which type of interpolation do you want? (neighbor, bilinear, bicubic) " << endl;
  string interpolation = "bicubic";
  cin >> interpolation;
  cout << "How many pairs of rotation do we do ? (1 already done)" << endl;
  int number_of_rotations = 0;
  cin >> number_of_rotations;
  dst.create( src.size(), src.type() );
  fill_dst(theta, centroid, src, dst, interpolation);
  Mat final;
  final.create( src.size(), src.type() );
  fill_dst(-theta, centroid, dst, final, interpolation);
  for (int i = 0; i < number_of_rotations; i++)
  {
    fill_dst(+theta, centroid, final, dst, interpolation);
    fill_dst(-theta, centroid, dst, final, interpolation);
  }
  time = clock();
  cout << " The program has taken : " << time << endl;
  Mat diff;
  subtract( src, final, diff);
  float errora = err(diff);
  cout << "The error with this interpolation method is : " << errora << endl;
  imshow( "remap", final );
  waitKey(0);
  return 0;
}
