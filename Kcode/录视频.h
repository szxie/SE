#include "stdafx.h"
#include "Edge.h"
#include "HSV.h"
#include "Circle.h"

using namespace cv;

char WindName[] = "video";

int main()
{
 	Mat frame;
	namedWindow( WindName, CV_WINDOW_NORMAL );
  	CvCapture* capture = cvCreateCameraCapture(-1);
	frame = cvQueryFrame( capture );
	VideoWriter writer("F:\\eyeDetection.avi", CV_FOURCC('M', 'J', 'P', 'G'), 5, frame.size());

    while( true ) {
    	frame = cvQueryFrame( capture );
		flip(frame, frame, 1);
		imshow(WindName, frame);
		writer<<frame;
      	char c=cvWaitKey(1000/24);
      	if(c==27)break;
  	}
 	return 0;
}

