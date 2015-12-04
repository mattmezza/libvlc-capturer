/*
 * VLCFullBufferException.h
 *
 *  Created on: Dec 4, 2015
 *      Author: biplab
 */

#ifndef VLCFULLBUFFEREXCEPTION_H_
#define VLCFULLBUFFEREXCEPTION_H_

#include <string>
#include <exception>

namespace biplab {
namespace video {
namespace exceptions {

class VLCFullBufferException: public std::exception {
public:
	VLCFullBufferException();
	virtual ~VLCFullBufferException();
	virtual const char * what();
private:
	std::string msg;
};

} /* namespace exceptions */
} /* namespace video */
} /* namespace biplab */
#endif /* VLCFULLBUFFEREXCEPTION_H_ */
