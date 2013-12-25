#include <cv.h>
#include <highgui.h>
#include <iostream>
#include "Binary.cpp"
#include "HSV.cpp"
#include "Circle.cpp"
using namespace cv;

const char WindName_local[] = "local";
const char WindName_filtered[] = "filted";
const string InputVideoPath = "../data/eyeDetection.avi";
const double Local_xMin = 0.45;
const double Local_xMax = 0.8;
const double Local_yMin = 0.2;
const double Local_yMax = 0.55;
const int wastedFrameCnt = 0;

extern int MaxH;
extern int MinH;
extern int MaxS;
extern int MinS;
extern int MaxV;
extern int MinV;

int main()
{
	Mat frame;
	int count = 0;
	namedWindow( WindName_local, CV_WINDOW_NORMAL );
	namedWindow( WindName_filtered, CV_WINDOW_NORMAL );
	namedWindow("Tmp", CV_WINDOW_NORMAL );
	namedWindow("T2", CV_WINDOW_NORMAL );
	Mat filted, binary;
	VideoCapture reader(0);
	if (!reader.isOpened())
		std::cout <<"fail\n";
		
	while( reader.read(frame) ) {
		flip(frame, frame, 1);
		Size sizeFrame = frame.size();

		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		HSV(local,local,filted);
		imshow("Tmp", filted);
		inRange(filted, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
		//	char b=cvWaitKey(10000000);
		//if(b==98)continue; 
		Circle(binary, local, local);
		//Contours(binary,binary);
		//Binary(local, filted);
		imshow(WindName_filtered, binary);
		//char a=cvWaitKey(10000000);
		//if(a==97)continue;
		
		//Circle(binary, local, local);
		imshow("T2", local);
		frame.release();
		binary.release();
		filted.release();
		char c=cvWaitKey(1000/5);
		if(c==27)break;
	}
	return 0;
}

