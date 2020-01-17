#include "starter2_1.hpp"

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
  const char* remap_window = "Rotation demo";
  // angle of rotation in radians
  float theta = -0.68912; //(angle_1(deg)- angle_2(deg))/M_PI
  src = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE );
  dst.create( src.size(), src.type() ); //we create the destination image
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  Point p = find_centroid( src ); //we find the center of the rotation
  namedWindow( remap_window, WINDOW_AUTOSIZE );
  update_map_rotation( theta, p, map_x, map_y ); //we do the rotation of angle theta and center p
  remap( src, dst, map_x, map_y, INTER_AREA , BORDER_CONSTANT, Scalar(255) );
  Mat final;
  final.create( src.size(), src.type() ); //we create the destination image
  Mat mapf_x, mapf_y;
  mapf_x.create( src.size(), CV_32FC1 );
  mapf_y.create( src.size(), CV_32FC1 );
  update_map_rotation( -theta, p, mapf_x, mapf_y ); //we do the rotation of angle theta and center p
  remap( dst, final, mapf_x, mapf_y, INTER_CUBIC , BORDER_CONSTANT, Scalar(255) );
  Mat diff;
  subtract( src, final, diff);
  // Display results
  int error = err(diff);
  imshow( remap_window, dst );
  cout << "the error is: " << error << endl;
  cout << "The centroid is: " << Mat(p) << endl;
  cout << "The size of the image is: " << src.size() << endl;
  waitKey(0);
  return 0;
}
