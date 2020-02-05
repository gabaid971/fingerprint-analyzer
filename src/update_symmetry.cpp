/*!
 * \file update_symmetry.cpp
 * \brief Basic symmetry tool to feed the remap function of openCV
 * \author Daniel Gabaï
 */
#include "update_symmetry.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;


/*!
 * \fn void update_map_symmetry(Mat map_x, Mat map_y)
 * \brief Modify maps on the x and y axis to make a symmetry.
 *
 * \param map_x transformation according the x axis.
 * \param map_y transformation according the y axis. 
 */
void update_map_symmetry(Mat map_x, Mat map_y)
{
for( int j = 0; j < map_x.rows; j++ )
  {
  for( int i = 0; i < map_x.cols; i++ )
    {
      map_x.at<float>(j,i) = (float)(map_x.cols - i) ;
      map_y.at<float>(j,i) = (float) j ;
    }
  }
}
