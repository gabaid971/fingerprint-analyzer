#include "remap.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


float h0(float t)
{
    return (2*pow(t, 3) - 3*pow(t, 2) + 1);
}


float h1(float t)
{
    return (-2*pow(t, 3) + 3*pow(t, 2));
}


float h2(float t)
{
    return ( pow(t, 3) - 2*pow(t, 2) + t);
}


float h3(float t)
{
    return (pow(t, 3) - pow(t, 2));
}



float cubic_spline( Point p1, Point p2, Point p3, Point p4, float x)
{
  //encode hermite spline evaluated in x
  float x_trans = x - floor(x);
  return ( h0(x_trans)*p2.y + h1(x_trans)*p3.y + h2(x_trans)*(p2.y-p1.y) + h3(x_trans)*(p4.y-p3.y) );
}

/*
float cubic_spline( Point p1, Point p2, Point p3, Point p4, float x)
{ // lagrange polynomials evaluated in x
  return ( p1.y*((x-p2.x)*(x-p3.x)*(x-p4.x)) / ((p1.x-p2.x)*(p1.x-p3.x)*(p1.x-p4.x)) +  p2.y*((x-p1.x)*(x-p3.x)*(x-p4.x)) / ((p2.x-p1.x)*(p2.x-p3.x)*(p2.x-p4.x)) +  p3.y*((x-p1.x)*(x-p2.x)*(x-p4.x)) / ((p3.x-p1.x)*(p3.x-p2.x)*(p3.x-p4.x)) +  p4.y*((x-p1.x)*(x-p2.x)*(x-p3.x)) / ((p4.x-p1.x)*(p4.x-p2.x)*(p4.x-p3.x)) );
}
*/

uchar calculate_pixel_value( int x, int y, float theta, Point center, Mat src,  string interpolation )
{
  uchar value = 255; // the value of the rotated pixel, between 0 and 255
  float x_p = (float)(cos(-theta)*x + sin(-theta)*y + (1-cos(-theta))*center.x -sin(-theta)*center.y);
  float y_p = (float)(-sin(-theta)*x + cos(-theta)*y + sin(-theta)*center.x + (1-cos(-theta))*center.y);
  int i = (int) floor(x_p);
  int j = (int) floor(y_p);
  if (interpolation == "neighbor")
  {
    if (i > 0 && j > 0 && i < src.cols  && j < src.rows)
    {
      value = src.at<uchar>(j,i);
    }
  }
  if (interpolation == "bilinear")
  {
    if (i > 0 && j > 0 && i < src.cols  && j < src.rows )
    {
      float dir1 = (float)(src.at<uchar>(j, i+1) - src.at<uchar>(j, i));
      float x_trans = x_p - floor(x_p);
      float p1 = (float)src.at<uchar>(j, i) + dir1*x_trans;
      float dir2 = src.at<uchar>(j+1, i+1) - src.at<uchar>(j+1, i);
      float p2 = (float)src.at<uchar>(j+1, i) + dir2*x_trans;
      float y_trans = y_p - floor(y_p);
      float float_value = p1 + (p2-p1)*y_trans;
      if (float_value < 0)
      {
        float_value = 0;
      }
      if (float_value > 255)
      {
        float_value = 255;
      }
      value = (uchar) float_value;

    }
  }
  if (interpolation == "bicubic")
  {
    if (i > 0 && j > 0 && i < src.cols  && j < src.rows )
    {
      float p1 = cubic_spline( Point(i-1, src.at<uchar>(j-1, i-1)), Point(i, src.at<uchar>(j-1, i)), Point(i+1, src.at<uchar>(j-1, i+1)), Point(i+2, src.at<uchar>(j-1, i+2)), x_p);
      float p2 = cubic_spline( Point(i-1, src.at<uchar>(j, i-1)), Point(i, src.at<uchar>(j, i)), Point(i+1, src.at<uchar>(j, i+1)), Point(i+2, src.at<uchar>(j, i+2)), x_p);
      float p3 = cubic_spline( Point(i-1, src.at<uchar>(j+1, i-1)), Point(i, src.at<uchar>(j+1, i)), Point(i+1, src.at<uchar>(j+1, i+1)), Point(i+2, src.at<uchar>(j+1, i+2)), x_p);
      float p4 = cubic_spline( Point(i-1, src.at<uchar>(j+2, i-1)), Point(i, src.at<uchar>(j+2, i)), Point(i+1, src.at<uchar>(j+2, i+1)), Point(i+2, src.at<uchar>(j+2, i+2)), x_p);
      float float_value = cubic_spline( Point(j-1, p1), Point(j, p2), Point(j+1, p3), Point(j+2, p4), y_p);
      if (float_value < 0)
      {
        float_value = 0;
      }
      if (float_value > 255)
      {
        float_value = 255;
      }
      value = (uchar) float_value;
    }
  }
  return value;
}


void fill_dst(float theta, Point center, Mat src, Mat dst, string interpolation )
{
  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
       {
         dst.at<uchar>(j,i) = calculate_pixel_value( i, j, theta, center, src, interpolation );
       }
    }
}
