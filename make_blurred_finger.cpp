#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>

using namespace cv;
using namespace std;

/*
fn flip(Mat& kernel)
param kernel: kernel matrix
param temp: the extra matrix to save matrix during flipping matrix
return flipped matrix
*/

void flip(Mat& kernel)
{
	Mat temp;
	temp.create( kernel.size(), kernel.type());
	for (int i = 0; i < kernel.rows; i++)
		for (int j = 0;j < kernel.cols; j++)
			temp.at<float>(kernel.rows-i - 1,j) = kernel.at<float>(i,j);

	kernel = temp;
	for (int i = 0; i < kernel.cols; i++)
		for (int j = 0; j < kernel.rows; j++)
			temp.at<float>(j,kernel.cols-i-1) = kernel.at<float>(j,i);

	kernel = temp;
}

/*
fn padding(Mat &image, Mat kernel)
param kernel: kernel matrix
param image: original image matrix
param p: the number of row/ column which needs to pad
return matrix with padding zeros border
*/

void padding(Mat &image, Mat kernel){
  int p = (kernel.rows - 1)/2;
  copyMakeBorder(image, image, p, p, p, p, 0);
}

/*
fn convolution_2D(Mat image, Mat kernel)
param kernel: kernel matrix
param image: original image matrix
param r_i: the number of rows of original image before changing anything
param c_i: the number of cols of original image before changing anything
param O: output matrix (convolution matrix)
param sum: sum of product between kernel matrix and original image (it will be reset when kernel matrix is shifted )
return matrix after convolution
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

	imwrite( "blur.png", O); //save image
}

int main()
{
    Mat image,kernel;
		int kernel_size = 15;
		kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);
		for (int i = 0; i<kernel_size; i++)
		{
			for (int j = 0; j<kernel_size;j++){
				kernel.at<float>(i,j) = 500;
				if (i >= 1 && i <= 13)
					if (j>=1 && j <=13) kernel.at<float>(i,j) = 320;
				if (i >= 2 && i <= 12)
					if (j>=2 && j <=12) kernel.at<float>(i,j) = 210;
				if (i >= 3 && i <= 11)
						if (j>=3 && j <=11) kernel.at<float>(i,j) = 180;
				if (i >= 4 && i <= 10)
						if (j>=4 && j <=10) kernel.at<float>(i,j) = 150;
				if (i >= 5 && i <= 9)
					if (j>=5 && j <= 9) kernel.at<float>(i,j) = 110;
				if (i >= 6 && i <= 8)
					if (j>=6 && j <=8) kernel.at<float>(i,j) = 60;
				kernel.at<float>(7,7) = 1;
			}
		}

		int sum = 0;
		for (int i = 0; i<kernel_size; i++)
		{
			for (int j = 0; j<kernel_size;j++){
				sum = sum + kernel.at<float>(i,j);
			}
		}
		kernel = kernel/sum;

    image = imread( "clean_finger.png", IMREAD_GRAYSCALE); // Read the file
		if(image.empty())                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
		normalize(image,image,1,0,NORM_MINMAX,CV_32FC1);

    flip(kernel);
    padding(image, kernel);
    convolution_2D(image,kernel);

    return 0;
}
