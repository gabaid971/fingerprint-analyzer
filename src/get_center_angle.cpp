#include "get_center_angle.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>



//find the center of rotation
Point find_centroid(Mat src){
  Mat thr;
  threshold( src, thr, 100, 255,THRESH_BINARY );
  Moments m = moments(thr,true);
  Point p(m.m10/m.m00, m.m01/m.m00);
  return p;
}

//find the center of the ellipse
Point find_ellipse_center(Mat src){
  RotatedRect rect = get_rectangle(src);
  return rect.center;
}


//get the rectangle around the ellipse
RotatedRect get_rectangle(Mat src)
{
  Mat dst, thr, final;
  dst.create( src.size(), src.type() ); //we create the destination image
  thr.create( src.size(), src.type() );
  final.create( src.size(), src.type() );
  //Mat diff = difference_images(src, dst);
  // Display results
  boxFilter( src, dst, -1, Size(src.cols/10, src.cols/10) );
  threshold( dst, thr, 170, 255, THRESH_BINARY );
  Sobel( thr, final, -1, 1, 1 );
  //Sobel( final, final2, -1, 1, 1 );
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

//get the final image with the rectangle around the ellipse
Mat get_image(Mat src)
{
  Mat dst, thr, final;
  dst.create( src.size(), src.type() ); //we create the destination image
  thr.create( src.size(), src.type() );
  final.create( src.size(), src.type() );
  //Mat diff = difference_images(src, dst);
  // Display results
  boxFilter( src, dst, -1, Size(src.cols/10, src.cols/10) );
  threshold( dst, thr, 170, 255, THRESH_BINARY );
  Sobel( thr, final, -1, 1, 1 );
  //Sobel( final, final2, -1, 1, 1 );
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


//find the angle of rotation
float get_angle(Mat src){
  RotatedRect rect = get_rectangle(src);
  return rect.angle;
}

//find the size of the rectangle
Size get_size(Mat src){
  RotatedRect rect = get_rectangle(src);
  return rect.size;
}
