/*!
 * \file test_rectangle.cpp
 * \brief Use opencv functions. We just add a black rectangle on a fingreprint picture
 * \author Daniel Gabaï
 */
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
  Mat image;
  image = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE);
  // Check for invalid input
  if( image.empty() )
  {
    cout <<  "Could not open or find the image" << endl ;
    return -1;
  }
  imshow( "Input image", image );
  waitKey(0);
  rectangle(image, Point( 400, 300), Point( 430, 330), Scalar( 0 ), FILLED, LINE_8);
  imshow( "Transformed image", image );
  waitKey(0);
  return 0;
}
