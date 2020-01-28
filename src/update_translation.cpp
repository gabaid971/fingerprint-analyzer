#include "update_translation.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;


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
