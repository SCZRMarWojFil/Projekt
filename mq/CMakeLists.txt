## i have cmake 3.5
cmake_minimum_required(VERSION 3.5)
PROJECT(mq C CXX)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

## use this to globally use C++11 with in our project
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-Wall -Wformat=0")
#SET(CMAKE_EXE_LINKER_FLAGS  "-lrt")


add_executable(display_test src/display_image.cpp)
add_executable(producer src/producer.cpp src/mq_utils.cpp)
add_executable(consumer src/consumer.cpp src/mq_utils.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(display_test ${OpenCV_LIBS} )
target_link_libraries(producer ${OpenCV_LIBS} )
target_link_libraries(consumer ${OpenCV_LIBS} )
target_link_libraries(producer rt)
target_link_libraries(consumer rt)