#include "update_error.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{   /* this function only use opencv functions.
    we just add a black rectangle on a fingreprint picture */
    Mat image;
    image = imread( "images/fingerprint.jpg", IMREAD_GRAYSCALE); // Read the file
    imshow( "Display window", image );                // Show our image inside it.
    waitKey(0);
    return 0;
}
