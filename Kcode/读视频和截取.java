#include "stdafx.h"
#include "Edge.h"
#include "HSV.h"
#include "Circle.h"

using namespace cv;

const char WindName[] = "video";
const char* InputVideoPath = "F:\\eyeDetection.avi";
const double Local_xMin = 0.4;
const double Local_xMax = 0.8;
const double Local_yMin = 0.2;
const double Local_yMax = 0.5;
const int wastedFrameCnt = 50;

int main()
{
 	Mat frame;
	int count = 0;
	namedWindow( WindName, CV_WINDOW_NORMAL );
	VideoCapture reader(InputVideoPath);

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		++count;
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Local_xMin;
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName, local);
		cvWaitKey(1000/5);
  	}
 	return 0;
}

