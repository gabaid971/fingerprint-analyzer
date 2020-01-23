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
  Mat img;
  img = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  imshow( "remap", img );
  waitKey(0);
  threshold(img, img, 127, 255, cv::THRESH_BINARY);
  Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
  Mat temp;
  Mat eroded;
  imshow( "remap", img );
  waitKey(0);
  Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));

  bool done;
  do
  {
    erode(img, eroded, element);
    dilate(eroded, temp, element); // temp = open(img)
    subtract(img, temp, temp);
    bitwise_or(skel, temp, skel);
    eroded.copyTo(img);

    done = (countNonZero(img) == 0);
  } while (!done);
  Mat element2 = getStructuringElement(MORPH_OPEN, Size(3, 3));
  erode(skel, skel, element2);
  dilate(skel, skel, element2);
  imshow( "remap", skel );
  waitKey(0);
  return 0;
}
