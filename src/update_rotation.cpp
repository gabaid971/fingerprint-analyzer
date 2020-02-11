/*!
 * \file update_rotation.cpp
 * \brief Basic rotation tool to feed the remap function of openCV
 * \author Daniel Gabaï
 */
#include "update_rotation.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

/*!
 * \fn void update_map_rotation(Mat map_x, Mat map_y, Point center, float theta)
 * \brief Modify maps on the x and y axis to make a rotation.
 *
 * \param map_x transformation according the x axis.
 * \param map_y transformation according the y axis.
 * \param center center of the rotation.
 * \param theta angle of rotation.
 */
void update_map_rotation(Mat map_x, Mat map_y, Point center, float theta)
{
  for( int j = 0; j < map_x.rows; j++ )
  {
    for( int i = 0; i < map_x.cols; i++ )
    {
      map_x.at<float>(j,i) = (float)(cos(theta)*i + sin(theta)*j + (1-cos(theta))*center.x -sin(theta)*center.y);
      map_y.at<float>(j,i) = (float)(-sin(theta)*i + cos(theta)*j + sin(theta)*center.x + (1-cos(theta))*center.y);
    }
  }
}
