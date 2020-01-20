#include "error.hpp"
#include "translation_xy.hpp"
#include "update_translation.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


vector<int> best_translation_xy(Mat src, Mat obj)
{
  vector<int> indices(0,0);
  Mat diff;
  subtract(src, obj, diff);
  float error = err( diff );
  for (int i = -src.cols; i < src.cols; i++)
  {
    for (int j = -src.rows; j < src.rows; j++)
    {
      Mat map_x, map_y, dst;
      map_x.create( src.size(), CV_32FC1 );
      map_y.create( src.size(), CV_32FC1 );
      update_map_translation_xy(map_x, map_y, i, j);
      remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
      subtract(dst, obj, diff);
      float new_error = err(diff);
      if ( new_error < error)
      {
        error = new_error;
        indices[0] = i;
        indices[1] = j;
      }
    }
  }
  return indices;
}

/*
float translation_max_error_xy(Mat src, Mat obj)
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


float translation_min_error_xy(Mat src, Mat obj)
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


void draw_translation_xy(Mat src, Mat obj, Mat draw)
{
  Mat diff;
  for (int i = -src.cols; i < src.cols; i++)
  {
    for (int j = -src.rows; j < src.rows; j++)
    {
      Mat map_x, map_y, dst;
      map_x.create( src.size(), CV_32FC1 );
      map_y.create( src.size(), CV_32FC1 );
      update_map_translation_xy(map_x, map_y, i, j);
      remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
      subtract(dst, obj, diff);
      float new_error = err(diff);
      int point = (int)(new_error*10000);
      if (point < draw.rows)
      {
        imagePoints.push_back(Point((int)(src.cols+i), point));
      }
    }
  }
  polylines(draw, imagePoints, 0, Scalar(0));
}
*/
