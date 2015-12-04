/*
 * VLCElapsedTimeoutException.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: biplab
 */

#include "VLCElapsedTimeoutException.h"

namespace biplab {
namespace video {
namespace exceptions {

VLCElapsedTimeoutException::VLCElapsedTimeoutException() {
	msg = "Cannot open video stream, it took too much time.";
}

VLCElapsedTimeoutException::~VLCElapsedTimeoutException() {

}

const char * VLCElapsedTimeoutException::what() {
	return msg.c_str();
}

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
