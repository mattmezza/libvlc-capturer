/*
 * VLCAlreadyReadFrameException.h
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#ifndef VLCALREADYREADFRAMEEXCEPTION_H_
#define VLCALREADYREADFRAMEEXCEPTION_H_

#include <string>
#include <exception>

namespace biplab {
namespace video {
namespace exceptions {

class VLCAlreadyReadFrameException: public std::exception {
public:
	VLCAlreadyReadFrameException();
	virtual ~VLCAlreadyReadFrameException();
	virtual const char * what();
private:
	std::string msg;
};

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
#endif /* VLCALREADYREADFRAMEEXCEPTION_H_ */
