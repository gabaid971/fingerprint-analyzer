#include "finger_pressure.hpp"
#include "get_center_angle.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;

double distance_to(Point p1, Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y));
}

double c(double x, double y, float alpha, float r)
{
  return 0.5-tanh(sqrt(x*x+y*y/alpha) - r)/2;
}

uchar new_pixel(int i, int j, Point center, Mat trans, float alpha, float r){
  return (uchar)( c( abs(i-center.x), abs(j-center.y), alpha, r )*trans.at<uchar>(j,i));
}

Point choose_center(string center_type, Mat src)
{
  if (center_type == "ellipse_center")
  {
    Point center = find_ellipse_center(src);
    return center;
  }
  if (center_type == "centroid")
  {
    Point center = find_centroid(src);
    return center;
  }
  if (center_type == "image_center")
  {
    Point center = Point(src.cols/2, src.rows/2);
    return center;
  }
  return Point(src.cols/2, src.rows/2);
}
