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

	const int cColorWidth = 1920;
	const int cColorHeight = 1080;

	IKinectSensor* pKinectSensor = NULL;
	RGBQUAD* pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];

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


	IColorFrameSource* pColorFrameSource = NULL;
	hr = pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
	std::cout << "HR3:\t" << SUCCEEDED(hr) << std::endl;

	IColorFrameReader* pColorFrameReader = NULL;
	hr = pColorFrameSource->OpenReader(&pColorFrameReader);
	std::cout << "HR4:\t" << SUCCEEDED(hr) << std::endl;
	//SafeRelease(pColorFrameSource); TODO release later
	bool otherBool = pColorFrameReader;
	std::cout << "Other:\t" << otherBool << std::endl;
	//return hr


	//Update -- Main processing function
	IFrameDescription* pFrameDescription = NULL;
	hr = pColorFrameSource->get_FrameDescription(&pFrameDescription);
	std::cout << "HR5:\t" << SUCCEEDED(hr) << std::endl;

	int nWidth = 0;
	int nHeight = 0;
	hr = pFrameDescription->get_Width(&nWidth);
	hr = pFrameDescription->get_Height(&nHeight);
	std::cout << "Heigh-Width:\t" << nWidth << "--" << nHeight << std::endl;
	

	cv::Mat bufferMat(nHeight, nWidth, CV_8UC4);
	cv::Mat colorMat(nHeight / 2, nWidth / 2, CV_8UC4);
	unsigned int bufferSize = nWidth * nHeight * 4 * sizeof(unsigned char);
	cv::namedWindow("Kinect_Color");

	//ColorImageFormat imageFormat = ColorImageFormat_None;
	//hr = pColorFrameReader->AcquireLatestFrame(&pColorFrame);
	int i = 0;
	IColorFrame* pColorFrame = NULL;
	ColorImageFormat imageFormat = ColorImageFormat_None;
	while (++i < 100) {
		pColorFrame = NULL;
		hr = pColorFrameReader->AcquireLatestFrame(&pColorFrame);
		std::cout << "HR6." << i << ":\t" << SUCCEEDED(hr) << std::endl;
		if (SUCCEEDED(hr)) {
			pColorFrame->get_RawColorImageFormat(&imageFormat);
			std::cout << "HR7." << i << ":\t" << imageFormat << std::endl;
			if (imageFormat == ColorImageFormat_Yuy2) {
				hr = pColorFrame->CopyConvertedFrameDataToArray(bufferSize, reinterpret_cast<BYTE*>(bufferMat.data), ColorImageFormat::ColorImageFormat_Bgra);
				cv::resize(bufferMat, colorMat, cv::Size(), 0.5, 0.5);
				cv::imshow("Kinect_Color", colorMat);

				cv::waitKey(30);
				SafeRelease(pColorFrame);
			} else {
				std::cout << "HR8." << i << ":\t" << "ERRROROROROROROR" << std::endl;
			}



		}

		Sleep(60);


		// TODO Reminder color format may be YUY2 or YUYV
		//cv::cvtColor( bufferMat, colorMat, CV_YUV2BGR_YUYV );
	}
	
	//hr = pColorFrame->get_RawColorImageFormat(&imageFormat);

	//TODO More above

	//std::cout << "Image Format:\t" << imageFormat << std::endl;


	//TODO After working CColorBasics::~CColorBasics


	if (pKinectSensor) {
		pKinectSensor->Close();
	}
	SafeRelease(pKinectSensor);

	std::cout << "\n\nReturn to end program" << std::endl;
	std::cin.ignore();
	
	return 0;
}
