#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>

using namespace cv;
using namespace std;

void diff(Mat mt, Mat mt1){
  Mat diff;
  diff.create(mt.size(), CV_32FC1);
  for (int i = 0; i < mt.rows; i++){
    for (int j = 0; j < mt.cols; j++)
    {
      diff.at<float>(i,j) = mt.at<float>(i,j) - mt1.at<float>(i,j);
    }
  }

  normalize(diff,diff,255,0,NORM_MINMAX,CV_32SC1);
  imwrite( "Different.png", diff); //save image
}

int main(){
  Mat conv, confft;

  conv = imread( "convolution.png", IMREAD_GRAYSCALE); // Read the file
  if(conv.empty())                      // Check for invalid input
  {
      cout <<  "Could not open or find the image convolution" << endl ;
      return -1;
  }

  confft = imread( "convolution_FFT.png", IMREAD_GRAYSCALE); // Read the file
  if(confft.empty())                      // Check for invalid input
  {
    cout <<  "Could not open or find the image convolution fft" << endl ;
    return -1;
  }

  normalize(conv,conv,1,0,NORM_MINMAX,CV_32FC1);
  normalize(confft,confft,1,0,NORM_MINMAX,CV_32FC1);

  diff(conv,confft);

  return 0;
}
