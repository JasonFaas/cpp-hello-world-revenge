#include <iostream>
#include "opencv2/opencv.hpp"
#include <ppl.h>
//using namespace cv;

const std::string THIS_DIRECTORY = "C:/Users/jason/Desktop/Code/cpp-hello-world-revenge/Revenge/HelloOpenCV/";

cv::Mat depthImage, dilationDst, blackPixelsThreshold, medianBlackPixels, tempDepthImg, maskInv;

int dilation_iterations = 1;
int dilation_size = 20;
int threshVal = 25;
int const max_elem = 40;
int const max_kernel_size = 200;
int totalNumberOfPixels = 0;
void Dilation(int, void*);



int main() {
	std::cout << "Frame Operations Start" << std::endl;

	depthImage = cv::imread(THIS_DIRECTORY + "Depth_2018_11_26_10_50_10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	// Setup windows
	cv::namedWindow("depthImage");
	cv::imshow("depthImage", depthImage);

	cv::namedWindow("Dilation Demo");
	cv::namedWindow("Black_Pixels");

	// Display Total Pixel Info
	totalNumberOfPixels = depthImage.rows * depthImage.cols;
	std::cout << "Total Pixels:\t" << totalNumberOfPixels << std::endl;


	cv::createTrackbar("Iterations",
		"Dilation Demo",
		&dilation_iterations,
		max_elem,
		Dilation);
	cv::createTrackbar("Kernel size",
		"Dilation Demo",
		&dilation_size,
		max_kernel_size,
		Dilation);
	cv::createTrackbar("Threshold Value",
		"Dilation Demo",
		&threshVal,
		max_kernel_size,
		Dilation);
	Dilation(0, 0);

	int nonZero = cv::countNonZero(depthImage);
	int blackPixels = totalNumberOfPixels - nonZero;
	std::cout << "Black Pixels:\t" << blackPixels << std::endl;


	
	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}


void Dilation(int, void*)
{
	cv::Mat depthCopy;
	depthImage.copyTo(depthCopy);
	int dilation_type = cv::MORPH_RECT;
	int element_size = dilation_size * 2 + 1;
	cv::Mat element = cv::getStructuringElement(
		dilation_type,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));
	//dilate(depthImage, dilationDst, element, cv::Point(-1, -1), dilation_iterations);
	//cv::morphologyEx(depthImage, dilationDst, cv::MORPH_CLOSE, element, cv::Point(-1, -1), dilation_iterations);

	cv::Mat firstBlackPixelThresh;
	cv::threshold(depthCopy, firstBlackPixelThresh, threshVal, 255, cv::THRESH_BINARY_INV);

	//add white pixels to large areas of black pixels
	int soi = 3;
	int soiMid = 1;
	int soiStep = 2;
	Concurrency::parallel_for(0, depthCopy.rows - soi, soiStep, [&](int k) {
		Concurrency::parallel_for(0, depthCopy.cols - soi, soiStep, [&](int n) {
			cv::Rect roi = cv::Rect(n + soiMid, k + soiMid, soi, soi);

			cv::Mat roiImg = depthCopy(roi);

			double min, max;
			cv::minMaxLoc(roiImg, &min, &max);
			if ((int)max < 20) {
				depthCopy.at<uchar>(k + soiMid, n + soiMid) = 255;
			}
		});
	});
	
	
	//blur zero pixel areas
	//TODO: blur until no zero pixels
	firstBlackPixelThresh.copyTo(blackPixelsThreshold);
	for (int i = 0; i < std::max(dilation_iterations, 1); i++)
	{
		blackPixelsThreshold = NULL;
		medianBlackPixels = NULL;
		dilationDst = NULL;
		tempDepthImg = NULL;
		maskInv = NULL;
		cv::medianBlur(depthCopy, dilationDst, element_size);
		cv::threshold(depthCopy, blackPixelsThreshold, threshVal, 255, cv::THRESH_BINARY_INV);
		cv::bitwise_not(blackPixelsThreshold, maskInv);
		cv::bitwise_and(depthCopy, depthCopy, tempDepthImg, maskInv);
		cv::add(tempDepthImg, dilationDst, depthCopy, blackPixelsThreshold);

		std::cout << "Zero Pixels:\t" << cv::countNonZero(blackPixelsThreshold) << std::endl;
	}
	std::cout << "\n\n" << std::endl;

	imshow("Black_Pixels", blackPixelsThreshold);

	blackPixelsThreshold = NULL;
	medianBlackPixels = NULL;
	dilationDst = NULL;
	maskInv = NULL;
	tempDepthImg = NULL;
	cv::medianBlur(depthCopy, dilationDst, 5);
	cv::bitwise_not(firstBlackPixelThresh, maskInv);
	cv::bitwise_and(depthCopy, depthCopy, tempDepthImg, maskInv);
	cv::add(tempDepthImg, dilationDst, depthCopy, firstBlackPixelThresh);


	imshow("Dilation Demo", depthCopy);
}