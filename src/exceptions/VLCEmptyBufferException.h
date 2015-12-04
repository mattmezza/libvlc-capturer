/*
 * VLCEmptyBufferException.h
 *
 *  Created on: Nov 2, 2015
 *      Author: biplab
 */

#ifndef VLCEMPTYBUFFEREXCEPTION_H_
#define VLCEMPTYBUFFEREXCEPTION_H_

#include <string>
#include <exception>

namespace biplab {
namespace video {
namespace exceptions {

class VLCEmptyBufferException: public std::exception {
public:
	VLCEmptyBufferException();
	virtual ~VLCEmptyBufferException();
	virtual const char * what();
private:
	std::string msg;
};

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
#endif /* VLCEMPTYBUFFEREXCEPTION_H_ */
