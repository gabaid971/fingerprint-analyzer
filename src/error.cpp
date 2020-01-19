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


float best_translation(Mat src, Mat obj)
{
  Mat diff;
  subtract(src, obj, diff);
  float error = err( diff );
  int indice = 0;
  for (int i = -src.cols; i < src.cols; i++)
  {
    Mat map_x, map_y, dst;
    map_x.create( src.size(), CV_32FC1 );
    map_y.create( src.size(), CV_32FC1 );
    update_map_translation_x(map_x, map_y, i);
    remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
    subtract(dst, obj, diff);
    float new_error = err(diff);
    if ( new_error < error)
    {
      error = new_error;
      indice = i;
    }
  }
  return indice;
}

float translation_max_error(Mat src, Mat obj)
{
  Mat diff;
  subtract(src, obj, diff);
  float error = err( diff );
  for (int i = -src.cols; i < src.cols; i++)
  {
    Mat map_x, map_y, dst;
    map_x.create( src.size(), CV_32FC1 );
    map_y.create( src.size(), CV_32FC1 );
    update_map_translation_x(map_x, map_y, i);
    remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
    subtract(dst, obj, diff);
    float new_error = err(diff);
    if ( new_error > error)
    {
      error = new_error;
    }
  }
  return error;
}


float translation_min_error(Mat src, Mat obj)
{
  Mat diff;
  subtract(src, obj, diff);
  float error = err( diff );
  for (int i = -src.cols; i < src.cols; i++)
  {
    Mat map_x, map_y, dst;
    map_x.create( src.size(), CV_32FC1 );
    map_y.create( src.size(), CV_32FC1 );
    update_map_translation_x(map_x, map_y, i);
    remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
    subtract(dst, obj, diff);
    float new_error = err(diff);
    if ( new_error < error)
    {
      error = new_error;
    }
  }
  return error;
}


void draw_translation(Mat src, Mat obj, Mat draw)
{
  vector<Point> imagePoints;
  Mat diff;
  for (int i = -src.cols; i < src.cols; i++)
  {
    Mat map_x, map_y, dst;
    map_x.create( src.size(), CV_32FC1 );
    map_y.create( src.size(), CV_32FC1 );
    update_map_translation_x(map_x, map_y, i);
    remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
    subtract(dst, obj, diff);
    float new_error = err(diff);
    int point = (int)(new_error*10000);
    if (point < draw.rows)
    {
      imagePoints.push_back(Point((int)(src.cols+i), point));
    }
  }
  polylines(draw, imagePoints, 0, Scalar(0));
}
