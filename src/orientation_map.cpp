/*!
 * \file orientation_map.cpp
 * \brief Tools to get the orientation map of a fingerprint image
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

/*!
 * \fn Mat get_orientation_map(Mat src, int block_size)
 * \brief Computation of the orientation map.
 *
 * \param src input image.
 * \param block_size size of squared blocks which will divide the image.
 * \return the image of the orientation map.
 */
Mat get_orientation_map(Mat src, int block_size)
{
  Mat Fx(src.size(), CV_32F);
  Mat Fy(src.size(), CV_32F);
  Mat Fx_filter, Fy_filter;

  Mat smoothed(src.size(), CV_32F); //image with with the value of the angle in each block

  Mat result(src.size(), CV_32F); //image with lines in each block which indicates the direction

  Mat grad_x, grad_y;
  Sobel(src, grad_x, CV_32F, 1, 0, 3, 1, 0, BORDER_DEFAULT);
  Sobel(src, grad_y, CV_32F, 0, 1, 3, 1, 0, BORDER_DEFAULT);
  int block_x, block_y;
  for( int i = 0; i < src.cols; i+= block_size )
  {
    for( int j = 0; j < src.rows; j += block_size )
    {
      float Vx = 0;
      float Vy = 0;

      if( i > src.cols - block_size ) block_x = src.cols - i;
      else block_x = block_size;
      if( j > src.rows - block_size ) block_y = src.rows - j;
      else block_y = block_size;
      for( int k = i; k < i + block_x; k++ )
      {
        for( int l = j; l < j + block_y; l++ )
        {
          Vx += 2*grad_x.at<float>(j,i)*grad_y.at<float>(j,i);
          Vy += (grad_x.at<float>(j,i)*grad_x.at<float>(j,i)) - (grad_y.at<float>(j,i)*grad_y.at<float>(j,i));
        }
      }
      float theta =  0.5*fastAtan2(Vx, Vy)*M_PI/180;
      float value_x = cos(2*theta);
      float value_y = sin(2*theta);
      //fill blocks
      for( int k = i ; k < i + block_x; k++ )
      {
        for( int l = j ; l < j + block_y ; l++ )
        {
          Fx.at<float>(l,k) = value_x;
          Fy.at<float>(l,k) = value_y;
        }
      }
    }
  }
  GaussianBlur(Fx, Fx_filter, Size(5,5), 0);
  GaussianBlur(Fy, Fy_filter, Size(5,5), 0);
  for( int i = 0; i < src.cols; i++ )
  {
    for( int j = 0; j < src.rows; j ++ )
    {
      smoothed.at<float>(j,i) = 0.5*fastAtan2(Fy_filter.at<float>(j,i), Fx_filter.at<float>(j,i))*M_PI/180;
      if( (i%block_size)==0 && (j%block_size)==0 )
      {
        Point p1 = Point(i + (block_size/2)*(1+cos(smoothed.at<float>(j,i)-M_PI/2)), j + (block_size/2)*(1+sin(smoothed.at<float>(j,i)-M_PI/2)) );
        Point p2 = Point(i + (block_size/2)*(1-cos(smoothed.at<float>(j,i)-M_PI/2)) , j + (block_size/2)*(1-sin(smoothed.at<float>(j,i)-M_PI/2)) );
        line(result, p1, p2, Scalar(255), 1, CV_AA);
      }
    }
  }
  return result;
}
