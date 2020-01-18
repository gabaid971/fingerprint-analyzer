#include "update_rotation.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>

using namespace cv;

using namespace std;


void update_map_rotation(float theta, Point center, Mat map_x, Mat map_y)
{
  for( int j = 0; j < map_x.rows; j++ )
    { for( int i = 0; i < map_x.cols; i++ )
       {
           map_x.at<float>(j,i) = (float)(cos(theta)*i + sin(theta)*j + (1-cos(theta))*center.x -sin(theta)*center.y);
           map_y.at<float>(j,i) = (float)(-sin(theta)*i + cos(theta)*j + sin(theta)*center.x + (1-cos(theta))*center.y);
       }
    }
}
