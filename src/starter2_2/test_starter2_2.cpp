#include "starter2_2.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;


int main()
{
  Mat src, dst, thr, final;
  src = imread( "images/warp1_finger.png", IMREAD_GRAYSCALE );
  final = get_angle(src, dst, thr, final);
  imshow( "Angle", final );
  //int error = err(diff);
  //cout << "the error is: " << error << endl;
  waitKey(0);
  return 0;
}
