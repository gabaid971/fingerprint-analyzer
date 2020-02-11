/*!
 * \file error.cpp
 * \brief Comparison between two images.
 * \author Daniel Gabaï
 */
#include "error.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

/*!
 * \fn float err(Mat diff)
 * \brief Computation of the quadratic error.
 *
 * \param diff the difference between the two images to compare.
 * \return normalized quadratic error.
 */
float err(Mat diff)
{
  float sum = 0;
  float norm = 0;
  for( int j = 0; j < diff.rows; j++ )
  {
    for( int i = 0; i < diff.cols; i++ )
    {
      norm = norm + 255*255;
      sum = sum + (int)(diff.at<uchar>(j,i)*diff.at<uchar>(j,i));
    }
  }
  return ((float)(sum/norm));
}
