#include <iostream>
#include <vlc/vlc.h>

#include "VLCVideoCapture.h"
#include "VLCVideoCaptureContext.h"

using namespace biplab::video;
using namespace biplab::video::exceptions;

int main() {
	std::string camUrl = "rtsp://admin:123456@192.168.1.120:7070/stream1";
	std::string name = "varco120";
	std::string winname = "varco120";

	VLCVideoCapture* capturer = new VLCVideoCapture(camUrl, name, "RV24", 25,cv::Size(1920,1080), 200);

	capturer->open();

	int i = 0;
	cv::Mat frame;
	while(true) {
		try {
//			capturer->read(frame, 3);
			capturer->read(frame);
			cv::imshow(winname, frame);
			i++;
			if(cv::waitKey(30) >= 0) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(125));
		} catch (VLCAlreadyReadFrameException& e) {

		} catch(VLCEmptyBufferException& e) {
			std::cerr << e.what() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		} catch(VLCElapsedTimeoutException& e) {
			std::cerr << e.what() << std::endl;
			break;
		}
	}
	capturer->close();

	return 0;
}
