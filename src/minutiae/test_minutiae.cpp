#include "get_skeleton.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int connect_number(Mat src, int i, int j)
{
  int connect_number = abs(ctb(src, i-1 , j-1) - ctb(src, i , j-1)) + abs(ctb(src, i , j-1) - ctb(src, i+1 , j-1)) + abs(ctb(src, i+1 , j-1) - ctb(src, i+1 , j));
  connect_number +=  abs(ctb(src, i+1 , j) - ctb(src, i+1 , j+1)) + abs(ctb(src, i+1 , j+1) - ctb(src, i , j+1)) + abs(ctb(src, i , j+1) - ctb(src, i-1 , j+1));
  connect_number += abs(ctb(src, i-1 , j+1) - ctb(src, i-1 , j)) + abs(ctb(src, i-1 , j) - ctb(src, i-1 , j-1));
  return connect_number/2;
}


Mat find_minutiae(Mat src, int value)
{
  Mat minutiae_points(src.rows, src.cols, CV_8UC1, Scalar(255));
  for (int i = 1; i < src.cols - 1 ; i++)
  {
    for (int j = 1 ; j < src.rows - 1; j++)
    {
      if (src.at<uchar>(j,i) == 0)
      {
        if (connect_number(src, i, j) == value)
        {
          minutiae_points.at<uchar>(j,i) = 0;
        }
      }
    }
  }
  return minutiae_points;
}


int main()
{
  Mat src;
  src = imread( "images/perfect.jpg", IMREAD_GRAYSCALE );
  threshold(src, src, 127, 255, THRESH_BINARY);
  imshow( "YOUPI", src );
  waitKey(0);
  src = get_skeleton(src);
  Mat ending_points = find_minutiae(src, 1);
  Mat bifurcation_points = find_minutiae(src, 1);
  imshow( "YOUPI", ending_points );
  waitKey(0);
  //imwrite("warp1_skel1.png", src);
  return 0;
}
