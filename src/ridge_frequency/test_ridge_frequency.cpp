#include "normalize.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

Mat get_orientation_block(Mat src, int block_size)
{
  Mat Fx(src.size(), CV_32F);
  Mat Fy(src.size(), CV_32F);
  Mat Fx_filter, Fy_filter;

  Mat smoothed(src.size(), CV_32F); //image with with the value of the angle in each block

  Mat grad_x, grad_y;
  Sobel(src, grad_x, CV_32F, 1, 0, 3, 1, 0, BORDER_DEFAULT);
  Sobel(src, grad_y, CV_32F, 0, 1, 3, 1, 0, BORDER_DEFAULT);
  //Scharr(src, grad_x, CV_32F, 1, 0, 1, 0);
  //Scharr(src, grad_y, CV_32F, 0, 1, 1, 0);
  int block_x, block_y;
  for (int i = 0; i < src.cols; i+= block_size)
  {
    for (int j = 0; j < src.rows; j += block_size)
    {
      float Vx = 0;
      float Vy = 0;
      if (i > src.cols - block_size) block_x = src.cols - i;
      else block_x = block_size;
      if (j > src.rows - block_size) block_y = src.rows - j;
      else block_y = block_size;

      for (int k = i; k < i + block_x; k++)
      {
        for (int l = j; l < j + block_y; l++)
        {
          Vx += 2*grad_x.at<float>(j,i)*grad_y.at<float>(j,i);
          Vy += (grad_x.at<float>(j,i)*grad_x.at<float>(j,i)) - (grad_y.at<float>(j,i)*grad_y.at<float>(j,i));
        }
      }
      float theta =  0.5*fastAtan2(Vx, Vy)*M_PI/180;
      float value_x = cos(2*theta);
      float value_y = sin(2*theta);
      //fill blocks
      for ( int k = i ; k < i + block_x; k++)
      {
        for( int l = j ; l < j + block_y ; l++)
        {
          Fx.at<float>(l,k) = value_x;
          Fy.at<float>(l,k) = value_y;
        }
      }
    }
  }
  GaussianBlur(Fx, Fx_filter, Size(5,5), 0);
  GaussianBlur(Fy, Fy_filter, Size(5,5), 0);
  for (int i = 0; i < src.cols; i++)
  {
    for (int j = 0; j < src.rows; j ++)
    {
      smoothed.at<float>(j,i) = 0.5*fastAtan2(Fy_filter.at<float>(j,i), Fx_filter.at<float>(j,i))*M_PI/180;
    }
  }
  return smoothed;
}


vector<float> x_signature(Mat src, int i, int j, int block_size)
{
  vector<float> x_signature;
  Mat smoothed = get_orientation_block(src, block_size);
  float angle = smoothed.at<float>(j, i);
  cout <<" the angle is : " << angle << endl;
  for (int k = 0; k < 2*block_size; k++)
  {
    float value = 0;
    for (int d = 0; d < block_size; d++)
    {
      int u = (int)(i + (d - block_size/2)*cos(angle) + (k - block_size)*sin(angle));
      int v = (int)(j + (d - block_size/2)*sin(angle) - (k - block_size)*cos(angle));
      //if (u < 0) break;
      value += src.at<float>(v, u);
    }
    x_signature.push_back(value/(float)block_size);
    cout <<" signature: " << value/(float)block_size << endl;
  }
  return x_signature;
}


vector<float> deriv_signature(vector<float> x_signature)
{
  vector<float> deriv_signature;
  for (int i = 0; i < (int)(x_signature.size()-1); i++)
  {
    if (x_signature[i+1] > x_signature[i]) deriv_signature.push_back(1);
    if (x_signature[i+1] < x_signature[i]) deriv_signature.push_back(-1);
    if (x_signature[i+1] == x_signature[i]) deriv_signature.push_back(0);
  }
  return deriv_signature;
}


vector<float> second_deriv_signature(vector<float> deriv_signature)
{
  vector<float> second_deriv_signature;
  for (int i = 0; i < (int)(deriv_signature.size()-1); i++)
  {
    second_deriv_signature.push_back(deriv_signature[i+1] - deriv_signature[i]);
  }
  return second_deriv_signature;
}


int main()
{
  Mat src;
  src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE );
  src.convertTo(src, CV_32F, 1.0/255, 0);
  cout <<" type of the image: " << src.type()<< endl;
  vector<float> essai = x_signature(src, 8, 8, 8);
  vector<float> deriv_essai = deriv_signature(essai);
  //Mat smoothed = get_orientation_block(src, 8);
  //imshow( "Orientation map", smoothed );
  //waitKey(0);
  return 0;
}
