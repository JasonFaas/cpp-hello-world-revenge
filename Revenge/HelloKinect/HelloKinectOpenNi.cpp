#include <iostream>
#include "Kinect.h"
#include "OpenNI.h"

#include "opencv2/opencv.hpp"
using namespace cv;




int main() {
	std::cout << "\nHello, World OpenCV!" << std::endl;


	VideoCapture cap(CAP_OPENNI2); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat depthMap;
	Mat bgrImage;


	namedWindow("depth", 1);
	namedWindow("bgr", 1);
	for (;;)
	{

		cap.grab();
		cap.retrieve(depthMap, 0);
		cap.retrieve(bgrImage, 5); // up to 7
		imshow("depth", depthMap);
		imshow("bgr", bgrImage);

		//Mat frame;
		//cap >> frame; // get a new frame from camera
		//imshow("edges", frame);
		if (waitKey(30) >= 0) break;
	}
	// camera will be deinitialized automatically in VideoCapture destructor
	destroyAllWindows();
	
	std::cout << "\n\nReturn to end program" << std::endl;
	std::cin.ignore();
	
	return 0;
}
