# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(ImageCompression)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV package installed in the system
find_package(OpenCV REQUIRED)

# Include the directories where OpenCV headers are located
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the executable target (your .cpp file)
add_executable(test main.cpp CompressionImage.cpp CompresseurFactory.cpp ProcesseurImage.cpp GestionnaireImage.cpp)

# Link the OpenCV libraries to your project
target_link_libraries(test ${OpenCV_LIBS})