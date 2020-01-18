#include "finger_pressure.hpp"
#include "get_center_angle.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;

int main()
{
  Mat src, trans, dst, last;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  dst.create( src.size(), src.type() );
  trans.create( src.size(), src.type() );
  last.create( src.size(), src.type() );
  cout << "Which center do you want to choose? (ellipse_center, centroid, image_center)" << endl;
  string center_type;
  cin >> center_type;
  Point center = choose_center(center_type, src);
  Size rect_size = get_size(src);
  float alpha = (float)(rect_size.height)/(float)(rect_size.width);
  float r = 80;
  //imshow( "maincourse1", src);
  for( int j = 0; j < src.rows; j++ )
  {
    for( int i = 0; i < src.cols; i++ )
    {
         trans.at<uchar>(j,i) = (uchar)(255- src.at<uchar>(j,i));
    }
  }
  //imshow( "maincourse1", trans );
  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
         dst.at<uchar>(j,i) = new_pixel(i, j, center, trans, alpha, r);
     }
    }

  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
           last.at<uchar>(j,i) = (uchar)(255 - dst.at<uchar>(j,i));
      }
    }
  // Display results
  imshow( "Finger pressure", last );
  waitKey(0);
  return 0;
}
