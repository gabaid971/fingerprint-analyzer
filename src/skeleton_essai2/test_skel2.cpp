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
  return nb;
}


bool check_2_bis(Mat src, int i, int j )
{
  return (number_of_neigh(src, i,  j)>= 2 && number_of_neigh(src, i, j)<= 6);
}


bool check_3(Mat src, int i, int j, bool state )
{
  if (state)
  return !ctb(src, i, j+1) || !ctb(src, i-1, j) || !ctb(src, i, j-1);
  return !ctb(src, i-1, j) || !ctb(src, i, j+1) || !ctb(src, i+1, j);
}

bool check_4(Mat src, int i, int j, bool state )
{
  if (state)
  return !ctb(src, i-1, j) || !ctb(src, i+1, j) || !ctb(src, i, j-1);
  return !ctb(src, i, j+1) || !ctb(src, i+1, j) || !ctb(src, i, j-1);
}


int main()
{
  Mat src;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  threshold(src, src, 127, 255, THRESH_BINARY);
  for (int k = 1; k < 3; k++ )
    {
    for (int i = 1; i < src.cols - 1 ; i++)
    {
      for (int j = 1 ; j < src.rows - 1; j++)
      {
        if (src.at<uchar>(j,i) == 0)
        {
          if (check_1(src, i, j) && check_2_bis(src, i, j) && check_3(src, i, j, 1) && check_4(src, i, j, 1) ){
            src.at<uchar>(j,i) = 255;
          }
        }
      }
    }
    for (int i = 1; i < src.cols - 1 ; i++)
    {
      for (int j = 1 ; j < src.rows - 1; j++)
      {
        if (src.at<uchar>(j,i) == 0)
        {
          if (check_1(src, i, j) && check_2_bis(src, i, j) && check_3(src, i, j, 0) && check_4(src, i, j, 0) ){
            src.at<uchar>(j,i) = 255;
          }
        }
      }
    }
  }
  imshow( "jenaimarre", src );
  waitKey(0);
  return 0;
}
