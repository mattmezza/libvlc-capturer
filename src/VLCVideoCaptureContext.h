/*
 * VLCVideoCaptureContext.h
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#ifndef VLCVIDEOCAPTURECONTEXT_H_
#define VLCVIDEOCAPTURECONTEXT_H_

#include <mutex>
#include <iostream>
#include <opencv/cv.hpp>

#include "exceptions/VLCEmptyBufferException.h"
#include "exceptions/VLCFullBufferException.h"

using namespace biplab::video::exceptions;

namespace biplab {
namespace video {

class VLCVideoCaptureContext {
private:
	std::mutex bufferMutex;
	std::vector<cv::Mat> buffer;
	unsigned int max_size_buffer;
public:
	VLCVideoCaptureContext(std::string* name_, cv::Size sz, int cv_pixel_type, unsigned int buffer_max_size);
	virtual ~VLCVideoCaptureContext();
	void read(cv::Mat& dst);
	void read(cv::Mat& dst, int frameToSkip);
	void addToBuffer(cv::Mat& frame);
	cv::Mat* image;
	std::mutex* mutex;
	uchar* pixels;
	std::string* name;
	bool alreadyRead;
	bool valid;

};

} /* namespace video */
} /* namespace biplab */
#endif /* VLCVIDEOCAPTURECONTEXT_H_ */
