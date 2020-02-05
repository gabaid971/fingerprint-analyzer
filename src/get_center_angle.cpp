/*!
 * \file get_center_angle.cpp
 * \brief Find the center and the angle of rotation between one image
 and the rotation of this image.
 * \author Daniel Gabaï
 */
#include "get_center_angle.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>


/*!
 * \fn Point find_centroid(Mat src)
 * \brief Compute the barycenter of a fingerprint.
 *
 * \param src input image.
 * \return the barycenter point.
 */
Point find_centroid(Mat src){
  Mat thr;
  threshold( src, thr, 100, 255,THRESH_BINARY );
  Moments m = moments(thr,true);
  Point p(m.m10/m.m00, m.m01/m.m00);
  return p;
}


/*!
 * \fn Point find_ellipse_center(Mat src)
 * \brief Compute the center of the ellipse around the fingerprint.
 *
 * \param src input image.
 * \return the point of the center of the ellipse.
 */
Point find_ellipse_center(Mat src){
  RotatedRect rect = get_rectangle(src);
  return rect.center;
}


/*!
 * \fn RotatedRect get_rectangle(Mat src)
 * \brief Compute the nearest ellipse fitting to the fingerprint.
 *
 * \param src input image.
 * \return the rectangle around the ellipse.
 */
RotatedRect get_rectangle(Mat src)
{
  Mat dst, thr, final;
  dst.create( src.size(), src.type() ); //we create the destination image
  thr.create( src.size(), src.type() );
  final.create( src.size(), src.type() );
  boxFilter( src, dst, -1, Size(src.cols/10, src.cols/10) );
  threshold( dst, thr, 170, 255, THRESH_BINARY );
  Sobel( thr, final, -1, 1, 1 );
  vector<Point> vec;
  for( int j = 0; j < final.rows; j++ )
    { for( int i = 0; i < final.cols; i++ )
     {
       if ( final.at<uchar>(j,i) == 255 )
          {
          vec.push_back( Point(i, j) );
          }
      }
    }
  RotatedRect rect = fitEllipse(vec);
  Point2f vertices[4];
  rect.points(vertices);
  for (int i = 0; i < 4; i++)
    line(final, vertices[i], vertices[(i+1)%4], Scalar(255));
  return rect;
}


/*!
 * \fn Mat get_image(Mat src)
 * \brief Image with the rectangle around the ellipse.
 *
 * \param src input image.
 * \return image with the rectangle around the contour.
 */
Mat get_image(Mat src)
{
  Mat dst, thr, final;
  dst.create( src.size(), src.type() ); //we create the destination image
  thr.create( src.size(), src.type() );
  final.create( src.size(), src.type() );
  boxFilter( src, dst, -1, Size(src.cols/10, src.cols/10) );
  threshold( dst, thr, 170, 255, THRESH_BINARY );
  Sobel( thr, final, -1, 1, 1 );
  vector<Point> vec;
  for( int j = 0; j < final.rows; j++ )
    { for( int i = 0; i < final.cols; i++ )
     {
       if ( final.at<uchar>(j,i) == 255 )
          {
          vec.push_back( Point(i, j) );
          }
      }
    }
  RotatedRect rect = fitEllipse(vec);
  Point2f vertices[4];
  rect.points(vertices);
  for (int i = 0; i < 4; i++)
    line(final, vertices[i], vertices[(i+1)%4], Scalar(255));
  return final;
}


/*!
 * \fn Mat float get_angle(Mat src)
 * \brief Compute the angle the ellipse with respect to the y axis.
 *
 * \param src input image.
 * \return angle of the ellipse.
 */
float get_angle(Mat src){
  RotatedRect rect = get_rectangle(src);
  return rect.angle;
}


/*!
 * \fn Size get_size(Mat src)
 * \brief Compute the size of the rectangle around the ellipse.
 *
 * \param src input image.
 * \return size of the rectangle.
 */
//find the size of the rectangle
Size get_size(Mat src){
  RotatedRect rect = get_rectangle(src);
  return rect.size;
}
