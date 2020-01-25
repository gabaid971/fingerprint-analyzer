#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

bool ctb(Mat src, int i, int j )
{
  return src.at<uchar>(j,i) == 0;
}


bool check_1(Mat src, int i, int j )
{
  int x = !ctb(src, i-1, j-1) && (ctb( src, i, j-1 ) || ctb( src, i+1 , j-1 ));
  x += !ctb(src, i+1, j-1) && (ctb( src, i+1, j ) || ctb( src, i+1 , j+1 ));
  x += !ctb(src, i+1, j+1) && (ctb( src, i, j+1 ) || ctb( src, i-1 , j+1 ));
  x += !ctb(src, i-1, j+1) && (ctb( src, i-1, j ) || ctb( src, i-1 , j-1 ));
  return x == 1;
}


bool check_2(Mat src, int i, int j )
{
  int n1 = ctb(src, i-1, j-1)  || ctb( src, i , j-1 );
  n1 += ctb(src, i+1, j-1)  || ctb( src, i+1 , j);
  n1 += ctb(src, i+1, j+1)  || ctb( src, i , j+1 );
  n1 += ctb(src, i-1, j+1)  || ctb( src, i-1 , j );
  int n2 = ctb(src, i, j-1)  || ctb( src, i+1 , j-1 );
  n2 += ctb(src, i+1, j)  || ctb( src, i+1 , j+1 );
  n2 += ctb(src, i, j+1)  || ctb( src, i-1 , j+1 );
  n2 += ctb(src, i-1, j)  || ctb( src, i-1 , j-1 );
  return n1<n2 ? (n1 == 2 || n1 == 3):(n2 == 2 || n2 == 3);
}


bool check_3(Mat src, int i, int j, bool state )
{
  if (state)
  return !((ctb(src, i, j-1) || ctb(src, i+1, j-1) || !ctb(src, i-1, j)) && ctb(src, i-1, j-1) );
  return !((ctb(src, i, j+1) || ctb(src, i-1, j+1) || !ctb(src, i+1, j)) && ctb(src, i+1, j+1) );
}



vector<Point> step(Mat src, bool state, vector<Point> to_erase)
{
  for (int i = 1; i < src.cols - 1 ; i++)
  {
    for (int j = 1 ; j < src.rows - 1; j++)
    {
      if (src.at<uchar>(j,i) == 0)
      {
        if (check_1(src, i, j) && check_2(src, i, j) && check_3(src, i, j, state)){
          to_erase.push_back(Point(i,j));
        }
      }
    }
  }
  return to_erase;
}

float mean_grey(Mat src)
{
  float sum = 0;
  for (int i = 0; i < src.cols  ; i++)
  {
    for (int j = 0 ; j < src.rows ; j++)
    {
      sum += (float)src.at<uchar>(j,i);
    }
  }
  return sum/(src.cols*src.rows);
}

int main()
{
  Mat src;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  cout << "the mean is: " << mean_grey(src) << endl;
  threshold(src, src, 80, 255, THRESH_BINARY);
  imshow( "YOUPI", src );
  waitKey(0);
  for (int l = 1; l < 100; l++ )
  {
    vector<Point> to_erase;
    to_erase = step(src, 1, to_erase);
    for (unsigned int i = 0; i < to_erase.size(); i++)
    {
      src.at<uchar>(to_erase[i].y, to_erase[i].x) = 255;
    }
    to_erase = step(src, 0, to_erase);
    for (unsigned int i = 0; i < to_erase.size(); i++)
    {
      src.at<uchar>(to_erase[i].y, to_erase[i].x) = 255;
    }
  }
  imshow( "YOUPI", src );
  waitKey(0);
  //imwrite("warp1_skel1.png", src);
  return 0;
}
