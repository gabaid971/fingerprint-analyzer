/*!
 * \file test_different_convolution.cpp
 * \brief Difference between convolution and convolution_FFT
 * \author Thu Thao Huynh
 */
#include "filter_convolution.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
  Mat conv, confft;
  //conv is the matrix using convolution
  conv = imread( "convolution.png", IMREAD_GRAYSCALE); // Read the file
  if(conv.empty())                      // Check for invalid input
  {
      cout <<  "Could not open or find the image convolution" << endl ;
      return -1;
  }

  //confft is the matrix using convolution FFT
  confft = imread( "convolution_FFT.png", IMREAD_GRAYSCALE); // Read the file
  if(confft.empty())                      // Check for invalid input
  {
    cout <<  "Could not open or find the image convolution fft" << endl ;
    return -1;
  }

  normalize(conv,conv,1,0,NORM_MINMAX,CV_32FC1);
  normalize(confft,confft,1,0,NORM_MINMAX,CV_32FC1);

  diff(conv,confft);

  return 0;
}
