cmake_minimum_required(VERSION 3.11)
project(Revenge)

#set(CMAKE_CXX_STANDARD 14)

# Attempt V2
set(OpenCV_Main "C:/Users/jason/Desktop/OpenCV/opencv-3.4.3")
set(OpenCV_DIR "${OpenCV_Main}/build/install/x86/vc15/lib")

set(OpenCL_Main "C:/Intel/OpenCL/sdk")
set(OpenCL_DIR "${OpenCL_Main}/lib/x86")

find_package( OpenCV REQUIRED )
find_package( OpenCL REQUIRED )
include_directories(Revenge "${OpenCV_Main}/build/install/include")
include_directories(Revenge "${OpenCL_Main}/include")

#add_executable(Revenge Revenge/HelloWorld/OpenCVDisplayCamera.cpp)
add_executable(Revenge Revenge/HelloOpenCL/main.cpp)

target_link_libraries (Revenge "${OpenCV_DIR}/opencv_calib3d343.lib" "${OpenCV_DIR}/opencv_core343.lib" "${OpenCV_DIR}/opencv_dnn343.lib" "${OpenCV_DIR}/opencv_features2d343.lib" "${OpenCV_DIR}/opencv_flann343.lib" "${OpenCV_DIR}/opencv_highgui343.lib" "${OpenCV_DIR}/opencv_imgcodecs343.lib" "${OpenCV_DIR}/opencv_imgproc343.lib" "${OpenCV_DIR}/opencv_ml343.lib" "${OpenCV_DIR}/opencv_objdetect343.lib" "${OpenCV_DIR}/opencv_photo343.lib" "${OpenCV_DIR}/opencv_shape343.lib" "${OpenCV_DIR}/opencv_stitching343.lib" "${OpenCV_DIR}/opencv_superres343.lib" "${OpenCV_DIR}/opencv_video343.lib" "${OpenCV_DIR}/opencv_videoio343.lib" "${OpenCV_DIR}/opencv_videostab343.lib")
target_link_libraries (Revenge "${OpenCL_DIR}/OpenCL.lib")
