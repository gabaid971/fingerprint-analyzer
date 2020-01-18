#include "error.hpp"

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
 float best_angle(Mat src, Mat obj, float theta, Point p)
{
    error = err( src, obj );
    angle = 0;
    for (size_t i = 0; i < 20; i++)
    {
      update_map_rotation(angle +i/100], p);
      remap( src, dst, map_x, map_y, INTER_LINEAR , BORDER_CONSTANT, Scalar(255) );
      if (difference_images(dst, obj) < error)
      {
        error = difference_images(dst, obj);
        angle = i;
      }
    }
    return angle;
}*/
