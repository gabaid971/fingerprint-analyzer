/*!
 * \file test_finger_pressure.cpp
 * \brief Starting from a normal pressure fingerprint,
 we transform it into a weak pressure fingerprint.
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

using namespace cv;
using namespace std;

int main()
{
  Mat src, trans, dst, last;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  //Show the input image
  imshow( "Input image", src );
  waitKey(0);

  dst.create( src.size(), src.type() );
  trans.create( src.size(), src.type() );
  last.create( src.size(), src.type() );

  cout << "Which center do you want to choose? (ellipse_center, centroid, image_center)" << endl;
  string center_type;
  cin >> center_type;
  // Select the center choosen by the user
  Point center = choose_center(center_type, src);
  // Get the size of the rectangle around the ellipse
  Size rect_size = get_size(src);
  // Ratio between the big axis and the small one
  float alpha = (float)(rect_size.height)/(float)(rect_size.width);
  // Size of the half small axis (in pixel)
  float r = 80;
  // Swap black to white
  for( int j = 0; j < src.rows; j++ )
  {
    for( int i = 0; i < src.cols; i++ )
    {
         trans.at<uchar>(j,i) = (uchar)(255- src.at<uchar>(j,i));
    }
  }
  // Apply the c function
  for( int j = 0; j < src.rows; j++ )
  {
    for( int i = 0; i < src.cols; i++ )
    {
      dst.at<uchar>(j,i) = new_pixel(i, j, center, trans, alpha, r);
    }
  }
  // Swap black to white
  for( int j = 0; j < src.rows; j++ )
  {
    for( int i = 0; i < src.cols; i++ )
    {
      last.at<uchar>(j,i) = (uchar)(255 - dst.at<uchar>(j,i));
    }
  }
  // Display results
  imshow( "Finger pressure", last );
  waitKey(0);
  return 0;
}
