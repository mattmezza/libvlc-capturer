/*
 * VLCVideoCapture.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#include "VLCVideoCapture.h"

namespace biplab {
namespace video {

void *lock(void *data, void** p_pixels) {
	VLCVideoCaptureContext *ctx = (VLCVideoCaptureContext*)data;
	ctx->mutex->lock();
	*p_pixels = ctx->pixels;
//	ctx->alreadyRead = false;
	ctx->valid = true;

	return NULL;
}

void unlock(void *data, void *id, void *const *p_pixels) {
	VLCVideoCaptureContext *ctx = (VLCVideoCaptureContext*)data;
	cv::Mat frame = *ctx->image;
	try {
		ctx->addToBuffer(frame);
		ctx->mutex->unlock();
	} catch(VLCFullBufferException& e) {
		ctx->mutex->unlock();
		std::cerr << e.what() << std::endl;
	}
}

void display(void *data, void *id){
	VLCVideoCaptureContext *ctx = (VLCVideoCaptureContext*)data;
//	cv::Mat frame = *ctx->image;
//	ctx->bufferMutex.lock();
//	ctx->buffer.push_back(frame);
//	ctx->bufferMutex.unlock();
}

VLCVideoCapture::VLCVideoCapture(std::string url_, std::string windowName_, std::string four_cc_, unsigned int fps_, cv::Size size_, unsigned int buffer_size) {
	url = url_;
	size = size_;
	windowName = windowName_;
	four_cc = four_cc_;
	fps = fps_;
	millis = (unsigned int) round(1000/fps);
	opened = false;
	if(size.height<=0 && size.width<=0) {
		size = getSize();
	}
	buf_size = buffer_size;
	ctx = new VLCVideoCaptureContext(&windowName, size, CV_8UC3, buffer_size);
}

VLCVideoCapture::~VLCVideoCapture() {
	delete ctx;
}

bool VLCVideoCapture::open() {
	if(isOpened())
		return true;
	std::vector<const char*> options;
	options.push_back("-I");
	options.push_back("dummy");
	options.push_back("--ignore-config");
	std::vector<const char*>::iterator option;
	// Load the VLC engine
	vlcInstance = libvlc_new(int(options.size()), options.data());
	// Create a media item from URL
	media = libvlc_media_new_location (vlcInstance, url.c_str());
	mp = libvlc_media_player_new_from_media (media);

	libvlc_video_set_callbacks(mp, lock, unlock, display, ctx);
	libvlc_video_set_format(mp, four_cc.c_str(), size.width, size.height, size.width * 24 / 8);

	libvlc_media_player_play(mp);

	opened = true;
	return isOpened();
}

void VLCVideoCapture::read(cv::Mat &frame, int frameToSkip) {
	if(!valid) {
		waitForValidBuffer();
	}
	ctx->read(frame, frameToSkip);
}

void VLCVideoCapture::read(cv::Mat &frame) {
//	if(!valid) {
//		waitForValidBuffer();
//	}
	ctx->read(frame);
}

cv::Mat VLCVideoCapture::read() {
	if(!valid) {
		waitForValidBuffer();
	}

	ctx->mutex->lock();
	cv::Mat tframe = *ctx->image;
	cv::Mat frame = tframe.clone();
	if(ctx->alreadyRead) {
		frame.release();
		ctx->mutex->unlock();
		VLCAlreadyReadFrameException e;
		throw e;
	} else {
		ctx->alreadyRead = true;
		ctx->mutex->unlock();
		if (frame.data && frame.rows>0 && frame.cols>0) {
			return frame;
		} else {
			frame.release();
			VLCEmptyBufferException e;
			throw e;
		}
	}

}

void VLCVideoCapture::close() {
	if(!isOpened())
		return;
	opened = false;
	valid = false;
	libvlc_media_player_stop(mp);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));
	libvlc_media_player_release(mp);
	libvlc_media_release(media);
	libvlc_release(vlcInstance);

}

cv::Size VLCVideoCapture::getSize() {
	libvlc_instance_t *vlcInstanceT;
	libvlc_media_player_t *mpT;
	libvlc_media_t *mediaT;

	std::vector<const char*> options;
	options.push_back("-I");
	options.push_back("dummy");
	options.push_back("--ignore-config");

	vlcInstanceT = libvlc_new(options.size(), options.data());

	mediaT = libvlc_media_new_location(vlcInstanceT, url.c_str());
	mpT = libvlc_media_player_new_from_media(mediaT);

	libvlc_media_release(mediaT);
	libvlc_video_set_callbacks(mpT, NULL, NULL, NULL, NULL);
	libvlc_video_set_format(mpT, four_cc.c_str(), 100, 100, 100 * 24 / 8); // pitch = width * BitsPerPixel / 8
	//libvlc_video_set_format(mp, "RV32", 100, 100, 100 * 4);
	libvlc_media_player_play(mpT);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));//wait a while so that something get rendered so that size info is available
	unsigned int width = 0, height = 0;

	for (int i = 0; i < 30 && height == 0; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		libvlc_video_get_size(mpT, 0, &width, &height);

		if (width != 0 && height != 0)
			break;
	}
	if (width == 0 || height == 0) {
		width = 320;
		height = 180;
	}

	libvlc_media_player_stop(mpT);
	libvlc_release(vlcInstanceT);
	libvlc_media_player_release(mpT);
	return cv::Size(width, height);
}

void VLCVideoCapture::waitForValidBuffer() {
//	ctx->mutex->lock();
	valid = ctx->valid;
//	ctx->mutex->unlock();
	unsigned int init_millis = 128;
	double base = 1.5;
	unsigned int exp = 0;
	unsigned int total_millis = 0;
	unsigned int max_wait_millis_timeout = 10000;
	while(!valid) {
		if(total_millis>max_wait_millis_timeout) {
			VLCElapsedTimeoutException e;
			throw e;
		}
		unsigned int t = init_millis/std::pow(base, exp);
		total_millis+=t;
		if(t<100) {
			exp=-1;
		}
//		std::cerr << "Non valid buffer, waiting " << t << " millis"<< std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(t));
		exp++;
//		ctx->mutex->lock();
		valid = ctx->valid;
//		ctx->mutex->unlock();
	}
}



} /* namespace video */
} /* namespace biplab */
