#include "starter2_2.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;

//we create the image source and the destination one:
//Mat src, dst, thr, final, final2;

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
}
*/

Mat get_angle(Mat src, Mat dst, Mat thr, Mat final)
{
  dst.create( src.size(), src.type() ); //we create the destination image
  thr.create( src.size(), src.type() );
  final.create( src.size(), src.type() );
  //Mat diff = difference_images(src, dst);
  // Display results
  boxFilter( src, dst, -1, Size(30, 30) );
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
  cout << "the angle is : " << rect.angle << endl;
  return final;
}
