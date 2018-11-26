#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
//using namespace cv;

const std::string THIS_DIRECTORY = "C:/Users/jason/Desktop/Code/cpp-hello-world-revenge/Revenge/HelloOpenCV/";

int main() {
	std::cout << "Frame Operations Start" << std::endl;

	cv::Mat depth_image = cv::imread(THIS_DIRECTORY + "Depth_2018_11_26_10_50_10.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	const int totalNumberOfPixels = depth_image.rows * depth_image.cols;

	
	if (depth_image.data)
	{
		int nonZero = cv::countNonZero(depth_image);
		int blackPixels = totalNumberOfPixels - nonZero;
		std::cout << "Black Pixels:\t" << blackPixels << std::endl;
		std::cout << "Total Pixels:\t" << totalNumberOfPixels << std::endl;
	}

	cv::namedWindow("Depth_Image");
	cv::imshow("Depth_Image", depth_image);
	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}
