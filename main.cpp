#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

// OpenCV includes
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv; 
using namespace std;
Mat img;

const char* keys = 
{ 
   "{help h usage ? | | print this message}" 
    "{@image | | Image to process}" 
}; 

/**
 * @brief 
 * hi hi hi
 * @param argv 
 * @return int 
 */
int main(int argc, const char** argv) 
{ 
   CommandLineParser parser(argc, argv, keys); 
    parser.about("Chapter 4. PhotoTool v1.0.0"); 
    //If requires help show 
    if (parser.has("help")) 
   { 
       parser.printMessage(); 
       return 0; 
   } 

   String imgFile= parser.get<String>(0); 
    // Check if params are correctly parsed in his variables 
    if (!parser.check()) 
    { 
        parser.printErrors(); 
        return 0; 
    }
    // Load image to process 
    Mat img= imread(imgFile); 
    
    // Create window 
    namedWindow("Input");

    createButton("Show histogram", showHistoCallback, NULL, QT_PUSH_BUTTON, 0); 
    createButton("Equalize histogram", equalizeCallback, NULL, QT_PUSH_BUTTON, 0); 
    createButton("Lomography effect", lomoCallback, NULL, QT_PUSH_BUTTON, 0); 
    createButton("Cartoonize effect", cartoonCallback, NULL, QT_PUSH_BUTTON, 0);

    // Show image 
    imshow("Input", img); 
    
    waitKey(0); 
    return 0; 
}

void showHistoCallback(int state, void* userData) 
{ 
    // Separate image in BRG 
    vector<Mat> bgr; 
    split(img, bgr); 
 
    // Create the histogram for 256 bins 
    // The number of possibles values [0..255] 
    int numbins= 256; 
 
    /// Set the ranges for B,G,R last is not included 
    float range[] = { 0, 256 } ; 
    const float* histRange = { range }; 
 
    Mat b_hist, g_hist, r_hist; 
 
    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &numbins, &histRange); 
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &numbins, &histRange); 
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &numbins, &histRange); 
 
    // Draw the histogram 
    // We go to draw lines for each channel 
    int width= 512; 
    int height= 300; 
    // Create image with gray base 
    Mat histImage(height, width, CV_8UC3, Scalar(20,20,20)); 
 
    // Normalize the histograms to height of image 
    normalize(b_hist, b_hist, 0, height, NORM_MINMAX); 
    normalize(g_hist, g_hist, 0, height, NORM_MINMAX); 
    normalize(r_hist, r_hist, 0, height, NORM_MINMAX); 
 
    int binStep= cvRound((float)width/(float)numbins); 
    for(int i=1; i< numbins; i++) 
    { 
        line(histImage,  
                Point( binStep*(i-1), height-cvRound(b_hist.at<float>(i-1) )), 
                Point( binStep*(i), height-cvRound(b_hist.at<float>(i) )), 
                Scalar(255,0,0) 
            ); 
        line(histImage,  
                Point(binStep*(i-1), height-cvRound(g_hist.at<float>(i-1))), 
                Point(binStep*(i), height-cvRound(g_hist.at<float>(i))), 
                Scalar(0,255,0) 
            ); 
        line(histImage,  
                Point(binStep*(i-1), height-cvRound(r_hist.at<float>(i-1))), 
                Point(binStep*(i), height-cvRound(r_hist.at<float>(i))), 
                Scalar(0,0,255) 
            ); 
    } 
 
    imshow("Histogram", histImage); 
 
} 