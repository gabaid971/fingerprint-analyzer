#include "update_symetry.hpp"

using namespace cv;

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>


int main()
{  /* use of the opencv function remap to make the symetry of a picture
  we will reimplement remap later for the rotation*/
  cv::Mat src, dst;
  cv::Mat map_x, map_y;
  const char* remap_window = "Symetry";
  src = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE );
  dst.create( src.size(), src.type() );
  map_x.create( src.size(), CV_32FC1 );
  map_y.create( src.size(), CV_32FC1 );
  namedWindow( remap_window, WINDOW_AUTOSIZE );

  update_map_symetry(src, map_x, map_y);
  remap( src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(255) );
  // Display results
  imshow( remap_window, dst );
  waitKey(0);
  return 0;
}
