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
  //we calculate the angle and the center of our image
  Mat src;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  Mat final = get_image(src);
  float angle = get_angle(src);
  Point ellipse_center = find_ellipse_center(src);
  Point centroid = find_centroid(src);
  imshow( "Angle and center", final );
  cout << "The centroid is: " << centroid << endl;
  cout << "The center of the ellipse is: " << ellipse_center << endl;
  cout << "The angle of the ellipse is: " << angle << endl;
  waitKey(0);
  return 0;
}
