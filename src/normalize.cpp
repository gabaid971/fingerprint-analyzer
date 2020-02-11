/*!
 * \file normalize.cpp
 * \brief Normalization of an image
 * \author Daniel Gabaï
 */
#include "normalize.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

/*!
 * \fn float mean_grey(Mat src)
 * \brief Calculus of the mean.
 *
 * \param src input image.
 * \return mean of pixels on the image.
 */
float mean_grey(Mat src)
{
  float sum = 0;
  for( int i = 0; i < src.cols  ; i++ )
  {
    for( int j = 0 ; j < src.rows ; j++ )
    {
      sum += (float)src.at<uchar>(j,i);
    }
  }
  return sum/(src.cols*src.rows);
}


/*!
 * \fn float var_grey(Mat src)
 * \brief Calculus of the variance.
 *
 * \param src input image.
 * \return variance of pixels on the image.
 */
float var_grey(Mat src)
{
  float sum = 0;
  float M = mean_grey(src);
  for( int i = 0; i < src.cols  ; i++ )
  {
    for( int j = 0 ; j < src.rows ; j++ )
    {
      sum += ((float)src.at<uchar>(j,i) - M )* ((float)src.at<uchar>(j,i) - M);
    }
  }
  return sum/(src.cols*src.rows);
}


/*!
 * \fn Mat normalize(Mat src, float mean, float var)
 * \brief Normalization of the image.
 *
 * \param src input image.
 * \param mean wanted mean.
 * \param var wanted variance.
 * \return normalized image.
 */
Mat normalize(Mat src, float mean, float var)
{
  float M = mean_grey(src);
  float V = var_grey(src);
  for( int i = 0; i < src.cols  ; i++ )
  {
    for( int j = 0 ; j < src.rows ; j++ )
    {
      if( (float)src.at<uchar>(j,i) <= M )
      {
        src.at<uchar>(j,i) = (uchar)(mean - sqrt( (var*((float)src.at<uchar>(j,i) - M)*((float)src.at<uchar>(j,i) - M))/V) );
      }
      if( M < (float)src.at<uchar>(j,i) )
      {
        src.at<uchar>(j,i) = (uchar)(mean + sqrt( (var*((float)src.at<uchar>(j,i) - M)*((float)src.at<uchar>(j,i) - M))/V) );
      }
    }
  }
  return src;
}
