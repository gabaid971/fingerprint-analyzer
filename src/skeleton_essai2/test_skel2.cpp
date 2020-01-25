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


int connect_number(Mat src, int i, int j)
{
  int connect_number = abs(ctb(src, i-1 , j-1) - ctb(src, i , j-1)) + abs(ctb(src, i , j-1) - ctb(src, i+1 , j-1)) + abs(ctb(src, i+1 , j-1) - ctb(src, i+1 , j));
  connect_number +=  abs(ctb(src, i+1 , j) - ctb(src, i+1 , j+1)) + abs(ctb(src, i+1 , j+1) - ctb(src, i , j+1)) + abs(ctb(src, i , j+1) - ctb(src, i-1 , j+1));
  connect_number += abs(ctb(src, i-1 , j+1) - ctb(src, i-1 , j)) + abs(ctb(src, i-1 , j) - ctb(src, i-1 , j-1));
  return connect_number/2;
}

bool check_1(Mat src, int i, int j)
{
  return connect_number(src, i ,j) == 1;
}


int number_of_neigh(Mat src, int i, int j)
{
  int nb = 0;
  for (int k = i-1 ; k < i+2; k++)
  {
    for (int l = j-1 ; l < j+2; l++)
    {
      nb += ctb(src, k , l);
    }
  }
  return nb-1;
}


bool check_2(Mat src, int i, int j )
{
  return (number_of_neigh(src, i,  j) >= 2 && number_of_neigh(src, i, j) <= 6);
}


bool check_3(Mat src, int i, int j, bool state )
{
  if (state)
  return !(ctb(src, i, j+1) && ctb(src, i+1, j) && ctb(src, i, j-1));
  return !(ctb(src, i-1, j) && ctb(src, i+1, j) && ctb(src, i, j-1));
}


bool check_4(Mat src, int i, int j, bool state )
{
  if (state)
  return !(ctb(src, i-1, j) && ctb(src, i+1, j) && ctb(src, i, j+1));
  return !(ctb(src, i, j-1) && ctb(src, i-1, j) && ctb(src, i, j+1));
}


vector<Point> step(Mat src, bool state, vector<Point> to_erase)
{
  for (int i = 1; i < src.cols - 1 ; i++)
  {
    for (int j = 1 ; j < src.rows - 1; j++)
    {
      if (src.at<uchar>(j,i) == 0)
      {
        if (check_1(src, i, j) && check_2(src, i, j) && check_3(src, i, j, state) && check_4(src, i, j, state) ){
          to_erase.push_back(Point(i,j));
        }
      }
    }
  }
  return to_erase;
}


int test_connect_nb()
{
  Mat src;
  src.create( Size(3,3), 0);
  src.at<uchar>(0,0) = 0;
  src.at<uchar>(0,1) = 0;
  src.at<uchar>(0,2) = 0;
  src.at<uchar>(1,0) = 255;
  src.at<uchar>(1,1) = 0;
  src.at<uchar>(1,2) = 255;
  src.at<uchar>(2,0) = 0;
  src.at<uchar>(2,1) = 0;
  src.at<uchar>(2,2) = 0;
  return number_of_neigh(src, 1, 1);
}

int main()
{
  //cout << test_connect_nb() << endl;
  Mat src;
  src = imread( "images/london.png", IMREAD_GRAYSCALE );
  threshold(src, src, 127, 255, THRESH_BINARY);
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
  imshow( "jenaimarre", src );
  waitKey(0);
  //imwrite("clean_skel.png", src);
  return 0;
}
