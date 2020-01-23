#include "error.hpp"
#include "translation_x.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{   /* opti for translation along x axis */
    Mat src, obj;
    src = imread( "images/clean_finger.png", IMREAD_GRAYSCALE);
    obj = imread( "images/tx_finger.png", IMREAD_GRAYSCALE);
    float min_error = translation_min_error(src, obj);
    float max_error = translation_max_error(src, obj);
    float indice = best_translation(src, obj);
    cout << "Le min de l'erreur vaut: " << min_error << endl;
    cout << "Le max de l'erreur vaut: " << max_error << endl;
    cout << "L'indice vaut: " << indice << endl;
    Mat draw(1000, 2*src.cols, CV_8UC1, Scalar(255));
    draw_translation(src, obj, draw);
    imshow( "Display window", draw );
    waitKey(0);
    return 0;
}