/*!
 * \file test_make_blurred_finger.cpp
 * \brief Blurred fingerprint
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
  Mat image,kernel;
  int kernel_size = 15;
  kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);
  for (int i = 0; i<kernel_size; i++)
  {
    for (int j = 0; j<kernel_size;j++){
      kernel.at<float>(i,j) = 500;
      if (i >= 1 && i <= 13)
      if (j>=1 && j <=13) kernel.at<float>(i,j) = 320;
      if (i >= 2 && i <= 12)
      if (j>=2 && j <=12) kernel.at<float>(i,j) = 210;
      if (i >= 3 && i <= 11)
      if (j>=3 && j <=11) kernel.at<float>(i,j) = 180;
      if (i >= 4 && i <= 10)
      if (j>=4 && j <=10) kernel.at<float>(i,j) = 150;
      if (i >= 5 && i <= 9)
      if (j>=5 && j <= 9) kernel.at<float>(i,j) = 110;
      if (i >= 6 && i <= 8)
      if (j>=6 && j <=8) kernel.at<float>(i,j) = 60;
      kernel.at<float>(7,7) = 1;
    }
  }

  int sum = 0;
  for (int i = 0; i<kernel_size; i++)
  {
    for (int j = 0; j<kernel_size;j++){
      sum = sum + kernel.at<float>(i,j);
    }
  }
  kernel = kernel/sum;

  image = imread( "images/clean_finger.png", IMREAD_GRAYSCALE); // Read the file
  if(image.empty())                      // Check for invalid input
  {
    cout <<  "Could not open or find the image" << endl ;
    return -1;
  }
  normalize(image,image,1,0,NORM_MINMAX,CV_32FC1);

  flip(kernel);
  padding(image, kernel);
  convolution_2D(image,kernel, "blur.png");

  return 0;
}
