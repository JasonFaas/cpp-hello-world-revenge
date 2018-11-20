#include <iostream>

#include "Windows.h"
#include "Ole2.h"
#include "Kinect.h"

bool initKinect(IKinectSensor* sensor, IColorFrameReader* reader) {
	GetDefaultKinectSensor(&sensor);
	if (!sensor) {
		return false;
	}
	if (sensor) {
		sensor->Open();

		IColorFrameSource* framesource = NULL;
		sensor->get_ColorFrameSource(&framesource);
		framesource->OpenReader(&reader);
		if (framesource) {
			framesource->Release();
			framesource = NULL;
		}
		return true;
	}
	else {
		return false;
	}
}

void getKinectData(IColorFrameReader* reader) {
	IColorFrame* frame = NULL;
	reader->AcquireLatestFrame(&frame);
	if (reader) {
		const int width = 1920;
		const int height = 1080;
		byte data[width * height * 4];
		//frame->CopyConvertedFrameDataToArray(width*height * 4, data, ColorImageFormat_Bgra);
		//frame->Release();
	}
	else {
		std::cout << "\nFailure to get Kinect Data" << std::endl;
	}

}

int main() {
	std::cout << "\nHello, World OpenGL!" << std::endl;

	IKinectSensor* sensor;
	IColorFrameReader* reader;


	if (!initKinect(sensor, reader)) {
		std::cout << "\nFailure to init Kinect" << std::endl;
		std::cin.ignore();
		return 1;
	}
	getKinectData(reader);



	
	std::cout << "\n\nReturn to end program" << std::endl;
	std::cin.ignore();
	
	return 0;
}
