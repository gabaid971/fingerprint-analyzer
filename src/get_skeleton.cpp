/*!
 * \file get_skeleton.cpp
 * \brief Thinning of a fingerprint
 * \author Daniel Gabaï
 */
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
 * \fn bool ctb(Mat src, int i, int j)
 * \brief Convert to boolean.
 *
 * \param src input image.
 * \param i position on x axis.
 * \param j position on y axis.
 * \return 1 if (i,j) is black, 0 else.
 */
bool ctb(Mat src, int i, int j)
{
  return src.at<uchar>(j,i) == 0;
}


/*!
 * \fn bool check_1(Mat src, int i, int j)
 * \brief First check for thinning : is the point (i,j) an ending point (crossing number = 1) ?.
 *
 * \param src input image.
 * \param i position on x axis.
 * \param j position on y axis.
 * \return 1 if (i,j) is an ending point, 0 else.
 */
bool check_1(Mat src, int i, int j)
{
  int x = !ctb(src, i-1, j-1) && (ctb( src, i, j-1 ) || ctb( src, i+1 , j-1 ));
  x += !ctb(src, i+1, j-1) && (ctb( src, i+1, j ) || ctb( src, i+1 , j+1 ));
  x += !ctb(src, i+1, j+1) && (ctb( src, i, j+1 ) || ctb( src, i-1 , j+1 ));
  x += !ctb(src, i-1, j+1) && (ctb( src, i-1, j ) || ctb( src, i-1 , j-1 ));
  return x == 1;
}


/*!
 * \fn bool check_2(Mat src, int i, int j)
 * \brief Second check for thinning.
 *
 * \param src input image.
 * \param i position on x axis.
 * \param j position on y axis.
 * \return boolean.
 */
bool check_2(Mat src, int i, int j)
{
  int n1 = ctb(src, i-1, j-1)  || ctb( src, i , j-1 );
  n1 += ctb(src, i+1, j-1)  || ctb( src, i+1 , j);
  n1 += ctb(src, i+1, j+1)  || ctb( src, i , j+1 );
  n1 += ctb(src, i-1, j+1)  || ctb( src, i-1 , j );
  int n2 = ctb(src, i, j-1)  || ctb( src, i+1 , j-1 );
  n2 += ctb(src, i+1, j)  || ctb( src, i+1 , j+1 );
  n2 += ctb(src, i, j+1)  || ctb( src, i-1 , j+1 );
  n2 += ctb(src, i-1, j)  || ctb( src, i-1 , j-1 );
  return n1<n2 ? (n1 == 2 || n1 == 3):(n2 == 2 || n2 == 3);
}


/*!
 * \fn bool check_3(Mat src, int i, int j, bool state)
 * \brief Third check for thinning.
 *
 * \param src input image.
 * \param i position on x axis.
 * \param j position on y axis.
 * \param state 1 for the first step, 0 for the second one.
 * \return boolean.
 */
bool check_3(Mat src, int i, int j, bool state)
{
  if (state)
  return !((ctb(src, i, j-1) || ctb(src, i+1, j-1) || !ctb(src, i-1, j)) && ctb(src, i-1, j-1) );
  return !((ctb(src, i, j+1) || ctb(src, i-1, j+1) || !ctb(src, i+1, j)) && ctb(src, i+1, j+1) );
}


/*!
 * \fn vector<Point> step(Mat src, bool state, vector<Point> to_erase)
 * \brief Fill a vector with all points which will be deleted after the first or second step.
 *
 * \param src input image.
 * \param state 1 for the first step, 0 for the second one.
 * \param to_erase vector with points to erase.
 * \return vector with new points to delete.
 */
vector<Point> step(Mat src, bool state, vector<Point> to_erase)
{
  for( int i = 1; i < src.cols - 1 ; i++ )
  {
    for( int j = 1 ; j < src.rows - 1; j++ )
    {
      if( src.at<uchar>(j,i) == 0 )
      {
        if( check_1(src, i, j) && check_2(src, i, j) && check_3(src, i, j, state) )
        {
          to_erase.push_back(Point(i,j));
        }
      }
    }
  }
  return to_erase;
}


/*!
 * \fn Mat get_skeleton(Mat src)
 * \brief Computation of the skeleton of an image with thinning.
 *
 * \param src input image.
 * \return image of the skeleton.
 */
Mat get_skeleton(Mat src)
{
  for( int l = 1; l < 100; l++ )
  {
    vector<Point> to_erase;
    to_erase = step(src, 1, to_erase);
    for( unsigned int i = 0; i < to_erase.size(); i++ )
    {
      src.at<uchar>(to_erase[i].y, to_erase[i].x) = 255;
    }
    to_erase = step(src, 0, to_erase);
    for( unsigned int i = 0; i < to_erase.size(); i++ )
    {
      src.at<uchar>(to_erase[i].y, to_erase[i].x) = 255;
    }
  }
  return src;
}
