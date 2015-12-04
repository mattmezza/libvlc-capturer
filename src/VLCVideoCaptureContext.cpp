/*
 * VLCVideoCaptureContext.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#include "VLCVideoCaptureContext.h"

namespace biplab {
namespace video {

VLCVideoCaptureContext::VLCVideoCaptureContext(std::string* name_, cv::Size sz, int cv_pixel_type, unsigned int buffer_max_size) {
	name = name_;
	mutex = new std::mutex();
	image = new cv::Mat(sz.height, sz.width, cv_pixel_type);
	pixels = (unsigned char *)image->data;
	alreadyRead = false;
	valid = false;
	max_size_buffer = buffer_max_size;
}

VLCVideoCaptureContext::~VLCVideoCaptureContext() {
	delete image;
	delete mutex;
	delete name;
}

void VLCVideoCaptureContext::addToBuffer(cv::Mat& frame) {
	bufferMutex.lock();
	if(buffer.size()<max_size_buffer) {
		buffer.push_back(frame.clone());
		std::cout << "producing --size "<<buffer.size()<< std::endl;
		bufferMutex.unlock();
	} else {
		bufferMutex.unlock();
		VLCFullBufferException e;
		throw e;
	}
}
void VLCVideoCaptureContext::read(cv::Mat& dst, int frameToSkip) {
	bufferMutex.lock();
	for(int i = 0; i < frameToSkip; i++) {
		if(!buffer.empty()) {
			buffer.erase(buffer.begin());
			std::cout << "skipping --size "<<buffer.size()<< std::endl;
		}
	}
	if(!buffer.empty()) {
		dst = buffer[0];
		buffer.erase(buffer.begin());
		std::cout << "consuming --size "<<buffer.size()<< std::endl;
		bufferMutex.unlock();
	} else {
		bufferMutex.unlock();
		VLCEmptyBufferException e;
		throw e;
	}
}

void VLCVideoCaptureContext::read(cv::Mat& dst) {
	bufferMutex.lock();
	if(!buffer.empty()) {
		dst = buffer[0];
		buffer.erase(buffer.begin());
		std::cout << "consuming --size "<<buffer.size()<< std::endl;
		bufferMutex.unlock();
	} else {
		bufferMutex.unlock();
		VLCEmptyBufferException e;
		throw e;
	}
}

} /* namespace video */
} /* namespace biplab */
