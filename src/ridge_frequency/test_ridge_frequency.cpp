/*!
 * \file test_ridge_frequency.cpp
 * \brief Starting from an image get the frequency of all 8*8 blocks, to apply the Gabor filter (not done in this project)
 * \author Daniel Gabaï
 */
#include "normalize.hpp"
#include "ridge_frequency.hpp"

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
  src.convertTo(src, CV_32F, 1.0/255, 0);
  //example number 1: let's create a sinusoidal vector and try to calculate its frequency
  vector<float> vague;
  vague.push_back(3);
  vague.push_back(2);
  vague.push_back(1);
  vague.push_back(2);
  vague.push_back(3);
  vague.push_back(2);
  vague.push_back(1);
  vague.push_back(2);
  vague.push_back(3);
  vague.push_back(2);
  float frequency_example = frequency(vague);
  cout <<" The frequency on the first example is : " << frequency_example << endl;
  //example number 2: let's try our function on clean_finger.png
  vector<float> x_sign = x_signature(src, 100, 100, 8);
  float ridge_frequency = frequency(x_sign);
  cout <<" The ridge frequency on the block centered on (100,100) is : " << ridge_frequency << endl;
  Mat smoothed = get_orientation_block(src, 8);
  imshow( "Orientation map with blocks of 8 by 8", smoothed );
  waitKey(0);
  return 0;
}
