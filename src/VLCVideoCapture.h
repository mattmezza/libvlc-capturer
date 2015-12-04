/*
 * VLCVideoCapture.h
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#ifndef VLCVIDEOCAPTURE_H_
#define VLCVIDEOCAPTURE_H_

#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
#include <chrono>
#include <cmath>

#include <opencv/cv.hpp>
#include <vlc/vlc.h>

#include "VLCVideoCaptureContext.h"
#include "exceptions/VLCAlreadyReadFrameException.h"
#include "exceptions/VLCEmptyBufferException.h"
#include "exceptions/VLCElapsedTimeoutException.h"

using namespace biplab::video;
using namespace biplab::video::exceptions;

namespace biplab {
namespace video {

class VLCVideoCapture {
public:
	VLCVideoCapture(std::string url_, std::string windowName_, std::string four_cc_, unsigned int fps_, cv::Size size_ = cv::Size(0, 0), unsigned int buffer_size = 60);
	virtual ~VLCVideoCapture();
	bool open();
	bool isOpened() {
		return opened;
	}
	cv::Mat read();
	void read(cv::Mat &frame);
	void read(cv::Mat &frame, int frameToSkip);
	void close();
	cv::Size getSavedSize() {return size;}
	std::string getFourCC() {return four_cc;}
private:
	bool opened;
	cv::Size size;
	std::string url;
	std::string four_cc;
	std::string windowName;
	unsigned int fps;
	VLCVideoCaptureContext* ctx;
	libvlc_instance_t *vlcInstance;
	libvlc_media_player_t *mp;
	libvlc_media_t *media;
	unsigned int millis;
	bool valid;
	unsigned int buf_size;

	cv::Size getSize();
	void waitForValidBuffer();
};

} /* namespace video */
} /* namespace biplab */
#endif /* VLCVIDEOCAPTURE_H_ */
