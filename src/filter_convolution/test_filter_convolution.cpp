/*!
 * \file test_filter_convolution.cpp
 * \brief Filter convolution application.
 * \author Thu Thao Huynh
 */
#include "filter_convolution.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;


int main()
{
    Mat image,kernel, input;
		int kernel_size = 3;
		kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);//(float)(kernel_size*kernel_size);
		kernel.at<float>(1,1) = 1;

    image = imread( "images/clean_finger.png", IMREAD_GRAYSCALE); // Read the file
		if(image.empty())                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
		normalize(image,image,1,0,NORM_MINMAX,CV_32FC1);

    flip(kernel);
    padding(image, kernel);
    convolution_2D(image,kernel, "convolution.png");

    waitKey(0);
    return 0;
}
