/*!
 * \file minutiae.cpp
 * \brief Tools to find some feature points on skeleton
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

/*!
 * \fn int crossing_number(Mat src, int i, int j)
 * \brief Compute the crossing number.
 *
 * \param src input image (skeleton).
 * \param i position on x axis.
 * \param j position on y axis.
 * \return crossing number.
 */
int crossing_number(Mat src, int i, int j)
{
  int crossing_number = abs(ctb(src, i-1 , j-1) - ctb(src, i , j-1)) + abs(ctb(src, i , j-1) - ctb(src, i+1 , j-1)) + abs(ctb(src, i+1 , j-1) - ctb(src, i+1 , j));
  crossing_number +=  abs(ctb(src, i+1 , j) - ctb(src, i+1 , j+1)) + abs(ctb(src, i+1 , j+1) - ctb(src, i , j+1)) + abs(ctb(src, i , j+1) - ctb(src, i-1 , j+1));
  crossing_number += abs(ctb(src, i-1 , j+1) - ctb(src, i-1 , j)) + abs(ctb(src, i-1 , j) - ctb(src, i-1 , j-1));
  return crossing_number/2;
}


/*!
 * \fn Mat find_minutiae(Mat src, int value)
 * \brief Creates an image with feature points on a skeleton.
 *
 * \param src input image.
 * \param value value of the crossing number (1 for ending points, 3 for bifurcation points)
 * \return image with feature points wished.
 */
Mat find_minutiae(Mat src, int value)
{
  Mat minutiae_points(src.rows, src.cols, CV_8UC1, Scalar(255));
  for( int i = 1; i < src.cols - 1 ; i++ )
  {
    for( int j = 1 ; j < src.rows - 1; j++ )
    {
      if( src.at<uchar>(j,i) == 0 )
      {
        if( crossing_number(src, i, j) == value )
        {
          minutiae_points.at<uchar>(j,i) = 0;
        }
      }
    }
  }
  return minutiae_points;
}
