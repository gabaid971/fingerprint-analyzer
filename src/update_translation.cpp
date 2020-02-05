/*!
 * \file update_translation.cpp
 * \brief Basic translation tool to feed the remap function of openCV
 * \author Daniel Gabaï
 */
#include "update_translation.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;


/*!
 * \fn void update_map_translation_x(Mat map_x, Mat map_y, int px)
 * \brief Modify maps on the x and y axis to make a translation along x axis.
 *
 * \param map_x transformation according the x axis.
 * \param map_y transformation according the y axis.
 * \param px translation along the x axis.
 */
void update_map_translation_x(Mat map_x, Mat map_y, int px)
{
  for( int j = 0; j < map_x.rows; j++ )
  {
    for( int i = 0; i < map_x.cols; i++ )
    {
      map_x.at<float>(j,i) = (float)(i + px) ;
      map_y.at<float>(j,i) = (float) j ;
    }
  }
}


/*!
 * \fn void update_map_translation_y(Mat map_x, Mat map_y, int py)
 * \brief Modify maps on the x and y axis to make a translation along y axis.
 *
 * \param map_x transformation according the x axis.
 * \param map_y transformation according the y axis.
 * \param py translation along the y axis.
 */
void update_map_translation_y(Mat map_x, Mat map_y, int py)
{
  for( int j = 0; j < map_x.rows; j++ )
  {
    for( int i = 0; i < map_x.cols; i++ )
    {
      map_x.at<float>(j,i) = (float) i ;
      map_y.at<float>(j,i) = (float)( j + py) ;
    }
  }
}


/*!
 * \fn void update_map_translation_xy(Mat map_x, Mat map_y, int px, int py)
 * \brief Modify maps on the x and y axis to make a translation along x and y axis.
 *
 * \param map_x transformation according the x axis.
 * \param map_y transformation according the y axis.
 * \param px translation along the x axis.
 * \param py translation along the y axis.
 */
void update_map_translation_xy(Mat map_x, Mat map_y, int px, int py)
{
  for( int j = 0; j < map_x.rows; j++ )
  {
    for( int i = 0; i < map_x.cols; i++ )
    {
      map_x.at<float>(j,i) = (float)(i + px) ;
      map_y.at<float>(j,i) = (float)(j + py) ;
    }
  }
}
