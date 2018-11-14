#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;


int main() {
	std::cout << "\nHello, World OpenCV!" << std::endl;


	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	
	namedWindow("edges", 1);
	for (;;)
	{
		std::cout << "TEST" << std::endl;

		Mat frame;
		cap >> frame; // get a new frame from camera
		imshow("edges", frame);
		if (waitKey(30) >= 0) break;
	}
	// camera will be deinitialized automatically in VideoCapture destructor
	destroyAllWindows();
	
	std::cout << "\n\nReturn to end program" << std::endl;
	std::cin.ignore();
	
	return 0;
}
