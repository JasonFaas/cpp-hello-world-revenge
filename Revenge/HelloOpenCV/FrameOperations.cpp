#include <iostream>
#include "opencv2/opencv.hpp"
//using namespace cv;

const std::string THIS_DIRECTORY = "C:/Users/jason/Desktop/Code/cpp-hello-world-revenge/Revenge/HelloOpenCV/";

cv::Mat depth_image, dilation_dst, black_pixels_threshold, median_black_pixels;

int dilation_iterations = 1;
int dilation_size = 20;
int const max_elem = 40;
int const max_kernel_size = 200;
void Dilation(int, void*);



int main() {
	std::cout << "Frame Operations Start" << std::endl;

	depth_image = cv::imread(THIS_DIRECTORY + "Depth_2018_11_26_10_50_10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	
	// Setup windows
	cv::namedWindow("Depth_Image");
	cv::imshow("Depth_Image", depth_image);

	cv::namedWindow("Dilation Demo");
	cv::namedWindow("Black_Pixels");

	// Display Total Pixel Info
	const int totalNumberOfPixels = depth_image.rows * depth_image.cols;
	std::cout << "Total Pixels:\t" << totalNumberOfPixels << std::endl;


	cv::createTrackbar("Iterations:\n 2n +1",
		"Dilation Demo",
		&dilation_iterations,
		max_elem,
		Dilation);
	cv::createTrackbar("Kernel size:\n 2n +1",
		"Dilation Demo",
		&dilation_size,
		max_kernel_size,
		Dilation);
	Dilation(0, 0);

	int nonZero = cv::countNonZero(depth_image);
	int blackPixels = totalNumberOfPixels - nonZero;
	std::cout << "Black Pixels:\t" << blackPixels << std::endl;


	
	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}


void Dilation(int, void*)
{
	cv::Mat depth_copy;
	depth_image.copyTo(depth_copy);
	int dilation_type = cv::MORPH_RECT;
	int element_size = dilation_size * 2 + 1;
		cv::Mat element = cv::getStructuringElement(
			dilation_type,
			cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
			cv::Point(dilation_size, dilation_size));
	//dilate(depth_image, dilation_dst, element, cv::Point(-1, -1), dilation_iterations);
	//cv::morphologyEx(depth_image, dilation_dst, cv::MORPH_CLOSE, element, cv::Point(-1, -1), dilation_iterations);
	
	for (int i = 0; i < std::max(dilation_iterations, 1); i++) 
	{
		black_pixels_threshold = NULL;
		median_black_pixels = NULL;
		dilation_dst = NULL;
		cv::medianBlur(depth_copy, dilation_dst, element_size);
		cv::threshold(depth_copy, black_pixels_threshold, 30, 255, cv::THRESH_BINARY_INV);
		//cv::bitwise_and(dilation_dst, dilation_dst, median_black_pixels, black_pixels_threshold);
		cv::add(depth_copy, dilation_dst, depth_copy, black_pixels_threshold);



		//TODO Black out those below threshold before median
	}
	imshow("Black_Pixels", black_pixels_threshold);
	imshow("Dilation Demo", depth_copy);
}