#include <iostream>

// includes
#include <Windows.h>
#include <Shlobj.h>
// Direct2D Header Files
#include <d2d1.h>
// Kinect Header files
#include <Kinect.h>
#include <strsafe.h>

#include "stdafx.h"

#include <opencv2/opencv.hpp>

int main() {
	std::cout << "\nHello, World Kinect Vanilla!" << std::endl;

	//const int cColorWidth = 1920;
	//const int cColorHeight = 1080;

	IKinectSensor* pKinectSensor = NULL;
	//RGBQUAD* pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];

	//CColorBasics InitializeDefaultSensor
	HRESULT hr = GetDefaultKinectSensor(&pKinectSensor);
	std::cout << "HR1:\t" << SUCCEEDED(hr) << std::endl;

	hr = pKinectSensor->Open();
	std::cout << "HR2:\t" << SUCCEEDED(hr) << std::endl;

	BOOLEAN isAvailable = NULL;
	int availableWaiter = 0;
	while (availableWaiter++ < 50) {
		pKinectSensor->get_IsAvailable(&isAvailable);
		if ((bool)isAvailable) {
			std::cout << "HR2." << availableWaiter << ":\t" << "Available!!!" << std::endl;
			break;
		}
		else {
			std::cout << "HR2." << availableWaiter << ":\t" << "Not Available" << std::endl;
			Sleep(100);
		}
	}


	IInfraredFrameSource* pInfraredFrameSource = NULL;
	hr = pKinectSensor->get_InfraredFrameSource(&pInfraredFrameSource);
	std::cout << "HR3:\t" << SUCCEEDED(hr) << std::endl;

	IInfraredFrameReader* pInfraredFrameReader = NULL;
	hr = pInfraredFrameSource->OpenReader(&pInfraredFrameReader);
	std::cout << "HR4:\t" << SUCCEEDED(hr) << std::endl;
	//SafeRelease(pInfraredFrameSource); TODO release later
	bool otherBool = pInfraredFrameReader;
	std::cout << "Other:\t" << otherBool << std::endl;
	//return hr


	//Update -- Main processing function
	IFrameDescription* pFrameDescription = NULL;
	hr = pInfraredFrameSource->get_FrameDescription(&pFrameDescription);
	std::cout << "HR5:\t" << SUCCEEDED(hr) << std::endl;

	int nWidth = 0;
	int nHeight = 0;
	hr = pFrameDescription->get_Width(&nWidth);
	hr = pFrameDescription->get_Height(&nHeight);
	std::cout << "Heigh-Width:\t" << nWidth << "--" << nHeight << std::endl;
	

	//cv::Mat bufferMat(nHeight, nWidth, CV_8UC4);
	cv::Mat irMat(nHeight, nWidth, CV_8UC1);
	cv::Mat hsvMat(nHeight, nWidth, CV_8UC3);
	//unsigned int bufferSize = nWidth * nHeight * 4 * sizeof(unsigned char);
	cv::namedWindow("Kinect_Depth");
	//cv::namedWindow("Kinect_Depth_Color");


	static const int        cInfraredWidth = 512;
	static const int        cInfraredHeight = 424;
	const UINT imgSize = nWidth * nHeight;
	UINT16 pixelData[cInfraredWidth * cInfraredHeight];

	//ColorImageFormat imageFormat = ColorImageFormat_None;
	//hr = pInfraredFrameReader->AcquireLatestFrame(&pInfraredFrame);
	int i = 0;
	IInfraredFrame* pInfraredFrame = NULL;
	//ColorImageFormat imageFormat = ColorImageFormat_None;

	int maxPixelValue = 0;

	while (++i < 100) {
		pInfraredFrame = NULL;
		hr = pInfraredFrameReader->AcquireLatestFrame(&pInfraredFrame);
		std::cout << "HR6." << i << ":\t" << SUCCEEDED(hr) << std::endl;
		if (SUCCEEDED(hr)) {
			hr = pInfraredFrame->get_InfraredFrameSource(&pInfraredFrameSource);
			std::cout << "HR7." << i << ":\t" << SUCCEEDED(hr) << std::endl;
			if (SUCCEEDED(hr)) {
				hr = pInfraredFrame->CopyFrameDataToArray(imgSize, pixelData);
				//cv::resize(bufferMat, colorMat, cv::Size(), 0.5, 0.5);
				//depthImage.at<UINT8>
				//cv::imshow("Kinect_Color", colorMat);
				int straightPixelPoint = 0;
				for (int k = 0; k < nHeight; k++) {
					for (int m = 0; m < nWidth; m++) {
						irMat.at<uchar>(k, m) = pixelData[straightPixelPoint] / 256;
						//hsvMat.at<uchar>(k, m, 0) = pixelData[straightPixelPoint] / 256;
						//hsvMat.at<uchar>(k, m, 1) = 200;
						//hsvMat.at<uchar>(k, m, 2) = 200;

						straightPixelPoint++;
					}
				}

				cv::imshow("Kinect_Depth", irMat);
				//cv::Mat bgrMat(nHeight, nWidth, CV_8UC3);
				//cv::cvtColor(hsvMat, bgrMat, cv::COLOR_HSV2BGR);
				//cv::imshow("Kinect_Depth_Color", hsvMat);

				cv::waitKey(30);
				SafeRelease(pInfraredFrame);
			} else {
				std::cout << "HR8." << i << ":\t" << "ERRROROROROROROR" << std::endl;
			}



		}

		Sleep(60);


		// TODO Reminder color format may be YUY2 or YUYV
		//cv::cvtColor( bufferMat, colorMat, CV_YUV2BGR_YUYV );
	}
	
	//hr = pInfraredFrame->get_RawColorImageFormat(&imageFormat);

	//TODO More above

	//std::cout << "Image Format:\t" << imageFormat << std::endl;


	//TODO After working CColorBasics::~CColorBasics


	if (pKinectSensor) {
		pKinectSensor->Close();
	}
	SafeRelease(pKinectSensor);

	std::cout << "\n\nReturn to end program" << maxPixelValue << std::endl;
	std::cin.ignore();
	
	return 0;
}
