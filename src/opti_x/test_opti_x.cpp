/*!
 * \file test_opti_x.cpp
 * \brief Comparison between an image and the same image translated on the x axis
 * \author Daniel Gabaï
 */
#include "error.hpp"
#include "translation_x.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{
    Mat src, obj;
    // Input image
    src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE);
    // Translated image
    obj = imread( "images/tx_finger.png", IMREAD_GRAYSCALE);
    float min_error = translation_min_error(src, obj);
    float max_error = translation_max_error(src, obj);
    // Calculus of the optimal parameter of translation
    float indice = best_translation(src, obj);
    cout << "The minimum of the error is: " << min_error << endl;
    cout << "The maximum of the error is: " << max_error << endl;
    cout << "The optimal parameter is: " << indice << endl;
    // Display results
    Mat draw(1000, 2*src.cols, CV_8UC1, Scalar(255));
    draw_translation(src, obj, draw);
    imshow( "Error function (0 is on the top)", draw );
    waitKey(0);
    return 0;
}
