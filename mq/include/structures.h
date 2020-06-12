#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <stdio.h> 
#include <chrono>

#include "common.h"
#include <opencv2/core/core.hpp>



// structure for message queue 
struct msg_buffer { 
  std::chrono::high_resolution_clock::time_point send_time;
  std::chrono::high_resolution_clock::time_point receive_time;
  std::chrono::high_resolution_clock::time_point processed_time;
  size_t total_size;
  int cv_type;
  int rows;
  int cols;
	char image_data[MAX_IMAGE_SIZE]; 
}; 

#endif /* #ifndef STRUCTURES_H_ */