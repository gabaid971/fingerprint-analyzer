/*!
 * \file filter_convolution.cpp
 * \brief Tools for filter convolution.
 * \author Thu Thao Huynh
 */
#include "filter_convolution.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>

using namespace cv;
using namespace std;

/*!
* \fn void flip(Mat& kernel)
* \param kernel: kernel matrix
* \return flipped matrix
*/
void flip(Mat& kernel)
{
	Mat temp;
	//flip matrix from bottom to top
	temp.create( kernel.size(), kernel.type());
	for (int i = 0; i < kernel.rows; i++)
		for (int j = 0;j < kernel.cols; j++)
			temp.at<float>(kernel.rows-i - 1,j) = kernel.at<float>(i,j);

	kernel = temp;
	//flip matrix from left to right
	for (int i = 0; i < kernel.cols; i++)
		for (int j = 0; j < kernel.rows; j++)
			temp.at<float>(j,kernel.cols-i-1) = kernel.at<float>(j,i);

	kernel = temp;
}


/*!
* \fn void padding(Mat &image, Mat kernel)
* \param kernel: kernel matrix
* \param image: original image matrix
* \return matrix with padding zeros border
*/

void padding(Mat &image, Mat kernel){
  int p = (kernel.rows - 1)/2;
  copyMakeBorder(image, image, p, p, p, p, 0);
}


/*
* \fn convolution_2D(Mat image, Mat kernel)
* \param kernel: kernel matrix
* \param image: original image matrix
* \return matrix after convolution
*/
void convolution_2D(Mat image, Mat kernel)
{
  int r_i = image.rows - kernel.rows + 1 ;
  int c_i = image.cols - kernel.cols + 1;

  Mat O;
  O.create(r_i,c_i, image.type());

  for (int i = 0; i < r_i; i++){
    for (int j = 0; j < c_i; j++)
    {
      float sum = 0;
      for (int k = 0; k < kernel.rows; k++){
        for (int l = 0; l < kernel.cols; l++)
        {
          sum = sum + kernel.at<float>(k,l)* image.at<float>(i+k, j+l);
        }
      }
			O.at<float>(i,j) = sum;
    }
  }
	normalize(O,O,255,0,NORM_MINMAX,CV_32SC1);

	imshow("Convolution",O); 
  waitKey(0);
}
