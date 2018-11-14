#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;


int main() {
	std::cout << "\nHello, World OpenCV!" << std::endl;


	//VideoCapture cap;
	//// open the default camera, use something different from 0 otherwise;
	//// Check VideoCapture documentation.
	//if (!cap.open(0))
	//	return 0;
	//for (;;)
	//{
	//	Mat frame;
	//	cap >> frame;
	//	if (frame.empty()) break; // end of video stream
	//	imshow("this is you, smile! :)", frame);
	//	if (waitKey(10) == 27) break; // stop capturing by pressing ESC 
	//}
	// the camera will be closed automatically upon exit
	// cap.close();



	std::cin.ignore();
	return 0;
}
