#include "finger_pressure.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;


int main()
{
  Mat src, trans, dst, last;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  dst.create( src.size(), src.type() );
  trans.create( src.size(), src.type() );
  last.create( src.size(), src.type() );
  namedWindow( "Fingerprint", WINDOW_AUTOSIZE );
  //imshow( "maincourse1", src);
  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
         trans.at<uchar>(j,i) = (uchar)(255- src.at<uchar>(j,i));
     }
    }

  //imshow( "maincourse1", trans );
  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
         dst.at<uchar>(j,i) = new_pixel(i, j, Point(src.cols/2, src.rows/2), trans);
     }
    }

  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
           last.at<uchar>(j,i) = (uchar)(255 - dst.at<uchar>(j,i));
      }
    }
  // Display results
  imshow( "maincourse1", last );
  waitKey(0);
  return 0;
}
