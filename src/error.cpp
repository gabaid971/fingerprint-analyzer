#include "error.hpp"
#include "update_rotation.hpp"
#include "update_translation.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

float err(Mat diff)
{ //returns the quadratic error
    float sum = 0;
    float norm = 0;
    for( int j = 0; j < diff.rows; j++ )
      { for( int i = 0; i < diff.cols; i++ )
         {
             norm = norm + 255*255;
             sum = sum + (int)(diff.at<uchar>(j,i)*diff.at<uchar>(j,i));
         }
      }
    return ((float)(sum/norm));
}

/*
 float best_translation(Mat src, Mat obj, Point p)
{
    subtract(src, obj, diff);
    error = err( diff );
    for (size_t i = -src.cols; i < src.cols; i++)
    {
      update_map_translation(map_x, map_y, i);
      remap( src, dst, map_x, map_y, INTER_LINEAR , BORDER_CONSTANT, Scalar(255) );
      subtract(dst, obj, diff)
      if ( err( diff )< error)
      {
        error = err( diff);
      }
    }
    return error;
}*/
