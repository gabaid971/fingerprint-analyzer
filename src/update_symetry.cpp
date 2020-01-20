#include "update_symetry.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

void update_map_symetry(Mat map_x, Mat map_y)
{
for( int j = 0; j < map_x.rows; j++ )
  {
  for( int i = 0; i < map_x.cols; i++ )
    {
      map_x.at<float>(j,i) = (float)(map_x.cols - i) ;
      map_y.at<float>(j,i) = (float) j ;
    }
  }
}
