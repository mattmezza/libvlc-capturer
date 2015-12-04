/*
 * VLCEmptyBufferException.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#include "VLCEmptyBufferException.h"

namespace biplab {
namespace video {
namespace exceptions {

VLCEmptyBufferException::VLCEmptyBufferException() {
	msg = "No frame fetched, buffer empty";
}

VLCEmptyBufferException::~VLCEmptyBufferException() {}

const char * VLCEmptyBufferException::what() {
	return msg.c_str();
}

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
