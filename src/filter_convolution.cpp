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

void padding(Mat &image, Mat kernel)
{
  int p = (kernel.rows - 1)/2;
  copyMakeBorder(image, image, p, p, p, p, 0);
}


/*
* \fn convolution_2D(Mat image, Mat kernel)
* \param kernel: kernel matrix
* \param image: original image matrix
* \return matrix after convolution
*/
void convolution_2D(Mat image, Mat kernel, string name)
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

	imwrite (name ,O);
}

/*!
* \fn DFT(Mat& image, Mat& kernel)
* \param image: matrix of original image
* \param kernel: matrix of kernel matrix
* \return the matrices which are discrete Fourier transform
*/
void DFT(Mat& image, Mat& kernel)
{
  // calculate the optimal DFT size
  int dftSize_col = getOptimalDFTSize(image.cols + kernel.cols - 1);
  int dftSize_row = getOptimalDFTSize(image.rows + kernel.rows - 1);

  //padding zero to get to optimal size
  copyMakeBorder(image, image, 0, dftSize_row - image.rows, 0, dftSize_col - image.cols,0);
  copyMakeBorder(kernel, kernel, 0, dftSize_row - kernel.rows, 0, dftSize_col - kernel.cols,0);

  //Discrete Fourier transform image and kernel
  dft(image,image);
  dft(kernel,kernel);
}


/*!
* \fn inverse(Mat image, Mat kernel,Mat save)
* \param image: matrix of original image
* \param kernel: matrix of kernel matrix
* \param save: matrix of original matrix before changing anything
* \return convolution FFT matrix
*/
void inverse(Mat image, Mat kernel,Mat save)
{
	DFT(image,kernel); //function to calculate DFT

  //Multiply element with element
	Mat dst;
	mulSpectrums(image, kernel, dst,false);

  //Inverse Discrete Fourier transform
  idft(dst,dst);

	normalize(dst,dst,255,0,NORM_MINMAX,CV_32SC1);

	//Cut to get the same size with original one
	Mat O(dst,Rect(0,0,save.cols,save.rows));

	imwrite( "convolution_FFT.png", O); //save image
}

/*!
* \fn void diff(Mat mt, Mat mt1)
* \param mt: the first matrix
* \param mt1: the second matrix
*/
void diff(Mat mt, Mat mt1)
{
  Mat diff;
  diff.create(mt.size(), CV_32FC1);
  for (int i = 0; i < mt.rows; i++)
  {
    for (int j = 0; j < mt.cols; j++)
    {
      diff.at<float>(i,j) = mt.at<float>(i,j) - mt1.at<float>(i,j);
    }
  }

  normalize(diff,diff,255,0,NORM_MINMAX,CV_32SC1);
  imwrite( "Different.png", diff); //save image
}
