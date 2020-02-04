#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void DFT(Mat& image, Mat& kernel){
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

void inverse(Mat image, Mat kernel,Mat save)
{
	DFT(image,kernel); //function to calculate DFT

  //Multiply element with element
	Mat dst;
  //dst.create(save.size());
	mulSpectrums(image, kernel, dst,false);

  //Inverse Discrete Fourier transform
  idft(dst,dst);

	normalize(dst,dst,255,0,NORM_MINMAX,CV_32SC1);

	//Cut to get the same size with original one
	Mat O(dst,Rect(0,0,save.cols,save.rows));

	imwrite( "convolution_FFT.png", O); //save image
}

int main()
{
    Mat image, kernel, save;
		int kernel_size = 3;
		kernel = Mat::ones( kernel_size, kernel_size, CV_32F)/(float)(kernel_size*kernel_size);

    image = imread( "clean_finger.png", IMREAD_GRAYSCALE); // Read the file

		if(image.empty())                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

		normalize(image,image,1,0,NORM_MINMAX,CV_32FC1);

    save = image;

		inverse(image,kernel,save);

    return 0;
}
