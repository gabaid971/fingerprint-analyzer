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
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
    rectangle(image,
           Point( 400, 300),
           Point( 430, 330),
           Scalar( 0 ),
           FILLED,
           LINE_8);
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image );                // Show our image inside it.
    //cout << (int)image.at<uchar>(311,420) << endl;
    waitKey(0); // Wait for a keystroke in the window
    imwrite( "modifie.png", image );
    return 0;
}
