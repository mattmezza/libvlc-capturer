/*
 * VLCAlreadyReadFrameException.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#include "VLCAlreadyReadFrameException.h"

namespace biplab {
namespace video {
namespace exceptions {

VLCAlreadyReadFrameException::VLCAlreadyReadFrameException() {
	msg = "The frame in the buffer that you are trying to read has been already read, you should skip it.";
}

VLCAlreadyReadFrameException::~VLCAlreadyReadFrameException() {}

const char * VLCAlreadyReadFrameException::what() {
	return msg.c_str();
}

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
