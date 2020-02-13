/*!
 * \file ridge_frequency.cpp
 * \brief Tools to get the frequency of a block to apply the Gabor filter (not done in this project)
 * \author Daniel Gabaï
 */
#include "normalize.hpp"
#include "ridge_frequency.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

/*!
 * \fn Mat get_orientation_block(Mat src, int block_size)
 * \brief Give the orientation angle of a block.
 * \param src input image.
 * \param block_size size of the block.
 * \return image with the value of the orientation angle in each block.
 */
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


/*!
 * \fn vector<float> x_signature(Mat src, int i, int j, int block_size)
 * \brief Find the window centered on the block and orthogonal to the orientation of this block.
 * \param src input image.
 * \param i center of the block on the x axis.
 * \param j center of the block on the y axis.
 * \param block_size size of blocks.
 * \return the vector of x_signature.
 */
vector<float> x_signature(Mat src, int i, int j, int block_size)
{
  vector<float> x_signature;
  Mat smoothed = get_orientation_block(src, block_size);
  float angle = smoothed.at<float>(j, i);
  for (int k = 0; k < 2*block_size; k++)
  {
    float value = 0;
    for (int d = 0; d < block_size; d++)
    {
      int u = (int)(i + (d - block_size/2)*cos(angle) + (k - block_size)*sin(angle));
      int v = (int)(j + (d - block_size/2)*sin(angle) - (k - block_size)*cos(angle));
      value += src.at<float>(v, u);
    }
    x_signature.push_back(value/(float)block_size);
  }
  return x_signature;
}


/*!
 * \fn vector<float> deriv_signature(vector<float>& x_signature)
 * \brief Derivation of a vector.
 * \param x_signature input vector.
 * \return derived vector.
 */
vector<float> deriv_signature(vector<float>& x_signature)
{
  vector<float> deriv_signatur;
  for (int i = 0; i < (int)(x_signature.size()-1); i++)
  {
    if (x_signature[i+1] > x_signature[i]) deriv_signatur.push_back(1);
    if (x_signature[i+1] < x_signature[i]) deriv_signatur.push_back(-1);
    if (x_signature[i+1] == x_signature[i]) deriv_signatur.push_back(0);
  }
  return deriv_signatur;
}


/*!
 * \fn vector<float> second_deriv_signature(vector<float>& deriv_signature)
 * \brief Second derivative of the vector.
 * \param deriv_signature input vector.
 * \return second derivate vector.
 */
vector<float> second_deriv_signature(vector<float>& deriv_signature)
{
  vector<float> second_deriv_signature;
  for (int i = 0; i < (int)(deriv_signature.size()-1); i++)
  {
    second_deriv_signature.push_back(deriv_signature[i] - deriv_signature[i+1]);
  }
  return second_deriv_signature;
}


/*!
 * \fn float frequency(vector<float>& x_signature)
 * \brief Find the frequency of a set of points stored in a vector.
 * \param x_signature input vector.
 * \return the frequency of the signal.
 */
float frequency(vector<float>& x_signature)
{
  vector<float> deriv_signatur = deriv_signature(x_signature);
  vector<float> second_deriv_signatur = second_deriv_signature(deriv_signatur);
  int nb_of_peaks = 0;
  vector<float> position_of_peaks;
  for (int i = 0; i < (int)(second_deriv_signatur.size()); i++)
  {
    if (second_deriv_signatur[i] == 2)
    {
      nb_of_peaks += 1;
      position_of_peaks.push_back(i);
    }
  }
  float frequency = -1;
  if (position_of_peaks.size() == 0) return frequency;
  if (position_of_peaks.size() == 1) return frequency;
  if (position_of_peaks.size() > 1)
  {
    frequency = (float)(position_of_peaks[0] - position_of_peaks[-1])/(float)(nb_of_peaks-1);
  }
  return frequency;
}
