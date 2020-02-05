/*!
 * \file translation_x.cpp
 * \brief Comparison between an image and the translated image on the x axis
 * \author Daniel Gabaï
 */
#include "error.hpp"
#include "translation_x.hpp"
#include "update_translation.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


/*!
 * \fn int best_translation(Mat src, Mat obj)
 * \brief Find the best translation parameter.
 *
 * \param src input image.
 * \param obj translated image.
 * \return number of pixels for the translation.
 */
int best_translation(Mat src, Mat obj)
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


/*!
 * \fn float translation_max_error(Mat src, Mat obj)
 * \brief Find the maximum of the quadratic error between the two images.
 *
 * \param src input image.
 * \param obj translated image.
 * \return maximum of the error function.
 */
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


/*!
 * \fn float translation_min_error(Mat src, Mat obj)
 * \brief Find the minimum of the quadratic error between the two images.
 *
 * \param src input image.
 * \param obj translated image.
 * \return minimum of the error function.
 */
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


/*!
 * \fn void draw_translation(Mat src, Mat obj, Mat draw)
 * \brief Draw the evolution of the quadratic error between the two images.
 *
 * \param src input image.
 * \param obj translated image.
 * \param draw image to draw the error function.
 */
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
