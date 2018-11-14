cmake_minimum_required(VERSION 3.11)
project(Revenge)

#set(CMAKE_CXX_STANDARD 14)


# V1
#set(OpenCV_Main "C:/Users/jason/Desktop/OpenCV/343exe/opencv")
#set(OpenCV_DIR "${OpenCV_Main}/build/x64/vc15/lib")

#find_package( OpenCV REQUIRED )
#include_directories(Revenge "${OpenCV_Main}/build/include")
#add_executable(Revenge Revenge/HelloWorld/OpenCVDisplayCamera.cpp)
#target_link_libraries (Revenge "${OpenCV_Main}/build/x64/vc15/lib/opencv_world343.lib")


# Attempt V2
# Maybe
# C:\Users\jason\Desktop\OpenCV\opencv-3.4.3\build\install\x86\vc15\lib
set(OpenCV_Main "C:/Users/jason/Desktop/OpenCV/opencv-3.4.3")
set(OpenCV_DIR "${OpenCV_Main}/build/install/x86/vc15/lib")

find_package( OpenCV REQUIRED )
include_directories(Revenge "${OpenCV_Main}/build/install/include")
add_executable(Revenge Revenge/HelloWorld/OpenCVDisplayCamera.cpp)
target_link_libraries (Revenge "${OpenCV_DIR}/opencv_calib3d343.lib" "${OpenCV_DIR}/opencv_core343.lib" "${OpenCV_DIR}/opencv_dnn343.lib" "${OpenCV_DIR}/opencv_features2d343.lib" "${OpenCV_DIR}/opencv_flann343.lib" "${OpenCV_DIR}/opencv_highgui343.lib" "${OpenCV_DIR}/opencv_imgcodecs343.lib" "${OpenCV_DIR}/opencv_imgproc343.lib" "${OpenCV_DIR}/opencv_ml343.lib" "${OpenCV_DIR}/opencv_objdetect343.lib" "${OpenCV_DIR}/opencv_photo343.lib" "${OpenCV_DIR}/opencv_shape343.lib" "${OpenCV_DIR}/opencv_stitching343.lib" "${OpenCV_DIR}/opencv_superres343.lib" "${OpenCV_DIR}/opencv_video343.lib" "${OpenCV_DIR}/opencv_videoio343.lib" "${OpenCV_DIR}/opencv_videostab343.lib")
