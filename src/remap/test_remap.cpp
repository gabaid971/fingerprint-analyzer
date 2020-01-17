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
  dst.create( src.size(), src.type() );
  fill_dst(theta, centroid, src, dst);
  Mat final;
  final.create( src.size(), src.type() );
  fill_dst(-theta, centroid, dst, final);
  Mat diff;
  subtract( src, final, diff);
  int errora = err(diff);
  cout << "the error is : " << errora << endl;
  imshow( "remap", diff );
  waitKey(0);
  return 0;
}
