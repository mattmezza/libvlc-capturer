/*
 * VLCFullBufferException.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: biplab
 */

#include "VLCFullBufferException.h"

namespace biplab {
namespace video {
namespace exceptions {

VLCFullBufferException::VLCFullBufferException() {
	msg = "Buffer full";
}

VLCFullBufferException::~VLCFullBufferException() {}

const char * VLCFullBufferException::what() {
	return msg.c_str();
}

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
