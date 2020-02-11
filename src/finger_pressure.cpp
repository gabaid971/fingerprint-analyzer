/*!
 * \file finger_pressure.cpp
 * \brief Tools to transform a hard pression fingerprint into a weak pression fingerprint.
 * \author Daniel Gabaï
 */
#include "finger_pressure.hpp"
#include "get_center_angle.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

/*!
 * \fn double distance_to(Point p1, Point p2)
 * \brief Computation of euclidian distance.
 *
 * \param p1 first point.
 * \param p2 second point.
 * \return distance between the two points.
 */
double distance_to(Point p1, Point p2)
{
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y));
}


/*!
 * \fn double c(double x, double y, float alpha, float r)
 * \brief Computation of the function c, giving an ellipsoid.
 *
 * \param x coordinate along the x axis.
 * \param y coordinate along the y axis.
 * \param alpha ratio between the big axis and the little axis of the ellipse.
 * \param r lenght of the half of the little axis.
 * \return value of the c function.
 */
double c(double x, double y, float alpha, float r)
{
  return 0.5-tanh(sqrt(x*x+y*y/alpha) - r)/2;
}


/*!
 * \fn float err(Mat diff)
 * \brief Computation of the quadratic error.
 *
 * \param diff the difference between the two images to compare.
 * \return normalized quadratic error.
 */
uchar new_pixel(int i, int j, Point center, Mat trans, float alpha, float r)
{
  return (uchar)( c( abs(i-center.x), abs(j-center.y), alpha, r )*trans.at<uchar>(j,i));
}


/*!
 * \fn Point choose_center(string center_type, Mat src)
 * \brief Choose between three type of center.
 *
 * \param center_type the type of center to choose between "ellipse_center", "centroid" and "image_center".
 * \param src input image.
 * \return coordinates of the center chosen.
 */
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
