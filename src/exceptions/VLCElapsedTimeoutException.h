/*
 * VLCElapsedTimeoutException.h
 *
 *  Created on: Nov 3, 2015
 *      Author: biplab
 */

#ifndef VLCELAPSEDTIMEOUTEXCEPTION_H_
#define VLCELAPSEDTIMEOUTEXCEPTION_H_

#include <string>
#include <exception>

namespace biplab {
namespace video {
namespace exceptions {

class VLCElapsedTimeoutException : public std::exception {
public:
	VLCElapsedTimeoutException();
	virtual ~VLCElapsedTimeoutException();
	virtual const char * what();
private:
	std::string msg;
};

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
#endif /* VLCELAPSEDTIMEOUTEXCEPTION_H_ */
