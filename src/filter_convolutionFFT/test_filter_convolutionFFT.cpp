/*!
 * \file test_filter_convolutionFFT.cpp
 * \brief Tools for filter FFT convolution.
 * \author Thu Thao Huynh
 */
 #include "filter_convolution.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
    Mat image, kernel, save;
		int kernel_size = 3;
		kernel = Mat::ones( kernel_size, kernel_size, CV_32F)/(float)(kernel_size*kernel_size);

    image = imread( "images/clean_finger.png", IMREAD_GRAYSCALE); // Read the file

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
