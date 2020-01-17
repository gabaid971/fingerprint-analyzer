#include "starter1_2.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

void update_map(Mat src, Mat map_x, Mat map_y)
{
  for( int j = 0; j < src.rows; j++ )
    { for( int i = 0; i < src.cols; i++ )
     {
         map_x.at<float>(j,i) = (float)(src.cols - i) ;
         map_y.at<float>(j,i) = (float) j ;
     }
    }
}
