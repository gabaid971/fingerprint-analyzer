#include "update_rotation.hpp"
#include "error.hpp"
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
  //we create the image source and the destination one:
  Mat src, dst;
  //and the mapping:
  Mat map_x, map_y;
  cout << "Choose the angle of rotation in radians" << endl;
  // angle of rotation in radians
  float theta = -0.68912; //(angle_1(deg)- angle_2(deg))/M_PI
  cin >> theta;
  src = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE );
  dst.create( src.size(), src.type() ); //we create the destination image
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  Point p = find_centroid( src ); //we find the center of the rotation
  update_map_rotation( map_x, map_y, p, theta ); //we do the rotation of angle theta and center p
  remap( src, dst, map_x, map_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
  Mat final;
  final.create( src.size(), src.type() ); //we create the destination image
  Mat mapf_x, mapf_y;
  mapf_x.create( src.size(), CV_32FC1 );
  mapf_y.create( src.size(), CV_32FC1 );
  update_map_rotation( mapf_x, mapf_y, p, -theta ); //we do the rotation of angle theta and center p
  remap( dst, final, mapf_x, mapf_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
  Mat diff;
  subtract( src, final, diff);
  // Display results
  float error = err(diff);
  imshow( "Rotation with opencv", dst );
  cout << "The error of the opencv remap function with bicubic interpolation is: " << error << endl;
  cout << "The centroid is: " << Mat(p) << endl;
  waitKey(0);
  return 0;
}
