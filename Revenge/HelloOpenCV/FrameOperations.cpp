#include <iostream>
#include "opencv2/opencv.hpp"
#include <ppl.h>
#include "SlamHelper.hpp"

const std::string THIS_DIRECTORY = "C:/Users/jason/Desktop/Code/cpp-hello-world-revenge/Revenge/HelloOpenCV/";

cv::Mat depthImage, dilationDst, blackPixelsThreshold, medianBlackPixels, tempDepthImg, maskInv;

int dilation_iterations = 1;
int const max_elem = 40;
int const max_kernel_size = 200;
int totalNumberOfPixels = 0;



int main() {

	std::cout << "Frame Operations Start" << std::endl;

	depthImage = cv::imread(THIS_DIRECTORY + "Depth_2018_11_26_10_50_10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	// Setup windows
	cv::namedWindow("depthImage");
	cv::imshow("depthImage", depthImage);


	//cv::createTrackbar("Iterations",
	//	"Dilation Demo",
	//	&dilation_iterations,
	//	max_elem,
	//	Dilation);
	//cv::createTrackbar("Kernel size",
	//	"Dilation Demo",
	//	&dilation_size,
	//	max_kernel_size,
	//	Dilation);
	//cv::createTrackbar("Threshold Value",
	//	"Dilation Demo",
	//	&threshVal,
	//	max_kernel_size,
	//	Dilation);

	SlamHelper* slamHelper = new SlamHelper();

	cv::Mat depthBlurred = slamHelper->blurGoodDataOverBad(depthImage);
	cv::namedWindow("Bad Data Blurred Out");
	imshow("Bad Data Blurred Out", depthBlurred);

	cv::Mat depthTo2d = slamHelper->depthTo2D(depthBlurred);
	cv::namedWindow("Depth to 2D");
	imshow("Depth to 2D", depthTo2d);
	
	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}
