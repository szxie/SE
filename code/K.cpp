#include <cv.h>
#include <highgui.h>
#include <iostream>
#include "Binary.cpp"
using namespace cv;

const char WindName_local[] = "local";
const char WindName_filtered[] = "filted";
const string InputVideoPath = "../data/eyeDetection.avi";
const double Local_xMin = 0.45;
const double Local_xMax = 0.8;
const double Local_yMin = 0.2;
const double Local_yMax = 0.55;
const int wastedFrameCnt = 0;

int main()
{
	Mat frame;
	int count = 0;
	namedWindow( WindName_local, CV_WINDOW_NORMAL );
	namedWindow( WindName_filtered, CV_WINDOW_NORMAL );
	createTrackbar("B1", WindName_filtered,&minV, 256);
	createTrackbar("B2", WindName_filtered,&maxV, 256);
	VideoCapture reader(0);
	if (!reader.isOpened())
		std::cout <<"fail\n";
		
	while( reader.read(frame) ) {
	//imshow(WindName, frame);
		++count;

		Size sizeFrame = frame.size();

		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		Mat filted;
		//HSV(local,local,filted);
		Binary(local, filted);
		imshow(WindName_filtered, filted);

		char c=cvWaitKey(1000/5);
		if(c==27)break;
	}
	return 0;
}
