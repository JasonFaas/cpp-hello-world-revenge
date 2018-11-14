cmake_minimum_required(VERSION 3.11)
project(Revenge)

#set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "C:/Users/jason/Desktop/OpenCV/343exe/opencv/build/x64/vc15/lib")

find_package( OpenCV REQUIRED )

include_directories(Revenge "C:/Users/jason/Desktop/OpenCV/343exe/opencv/build/include")

add_executable(Revenge Revenge/HelloWorld/OpenCVDisplayCamera.cpp)

target_link_libraries (Revenge "C:/Users/jason/Desktop/OpenCV/343exe/opencv/build/x64/vc15/lib/opencv_world343.lib")
