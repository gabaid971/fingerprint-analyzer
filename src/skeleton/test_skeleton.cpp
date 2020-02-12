/*!
 * \file test_skeleton.cpp
 * \brief We test our thinning algorithm on a fingerprint image to get the skeleton
 * \author Daniel Gabaï
 */
#include "get_skeleton.hpp"
#include "normalize.hpp"

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
  src = imread( "images/apres.png", IMREAD_GRAYSCALE );
  cout << "the mean is: " << mean_grey(src) << endl;
  cout << "the var is: " << var_grey(src) << endl;
  //src = normalize(src, 127, 5000);
  //GaussianBlur(src, src, Size(3,3), 0);
  imshow( "YOUPI", src );
  waitKey(0);
  threshold(src, src, 127, 255, THRESH_BINARY);
  imshow( "YOUPI", src );
  waitKey(0);
  src = get_skeleton(src);
  imshow( "YOUPI", src );
  waitKey(0);
  imwrite("skeleton.png", src);
  return 0;
}
