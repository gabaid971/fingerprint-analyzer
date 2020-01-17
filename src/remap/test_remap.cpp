#include "remap.hpp"

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
  Mat src;
  src = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE );
  Point centroid = find_centroid( src ); // center of rotation
  float theta =  0.68912 ; // angle of rotation
  Mat dst;
  cout << "Which type of interpolation do you want? (neighbor, bilinear, bicubic) " << endl;
  string interpolation = "bicubic";
  cin >> interpolation;
  cout << "How many pairs of rotation do we do ? (1 already done)" << endl;
  int number_of_rotations = 0;
  cin >> number_of_rotations;
  dst.create( src.size(), src.type() );
  fill_dst(theta, centroid, src, dst, interpolation);
  Mat final;
  final.create( src.size(), src.type() );
  fill_dst(-theta, centroid, dst, final, interpolation);
  for (int i = 0; i < number_of_rotations; i++)
  {
    fill_dst(+theta, centroid, final, dst, interpolation);
    fill_dst(-theta, centroid, dst, final, interpolation);
  }
  Mat diff;
  subtract( src, final, diff);
  float errora = err(diff);
  cout << "The error with this interpolation method is : " << errora << endl;
  imshow( "remap", final );
  waitKey(0);
  return 0;
}
