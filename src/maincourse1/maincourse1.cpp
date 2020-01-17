#include "maincourse1.hpp"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <math.h>
using namespace cv;

double distance_to(Point p1, Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y));
}

double c(double x, double y){
  return 0.5-tanh(sqrt(x*x+y*y/3) - 80)/2;
}

uchar new_pixel(int i, int j, Point center, Mat trans){
  return (uchar)( c( abs(i-center.x), abs(j-center.y) )*trans.at<uchar>(j,i));
}
