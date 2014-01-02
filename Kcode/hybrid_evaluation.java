#include "stdafx.h"
#include "Edge.h"
#include "HSV.h"
#include "Circle.h"
#include "Avg.h"
#include "evaluation.h"

using namespace cv;

const char WindName_local[] = "local";
const char WindName_filtered[] = "filtered";
const char* InputVideoPath = "C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\evaluation.avi";
extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;
const int wastedFrameCnt = 0;

extern int MinH;
extern int MinS;
extern int MinV;
extern int MaxH;
extern int MaxS;
extern int MaxV;
extern int evalSize;

int main()
{
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(InputVideoPath);
	point *tested_Avg = new point[evalSize];
	point *tested_Hough = new point[evalSize];

    while( reader.read(frame) ) {
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);

		Mat filtered,copyLocal = local.clone();
		HSV(local,local,filtered);
		inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
		bitwise_not(binary,binary);
		int x,y;
		averagePoint(binary,copyLocal,copyLocal,x,y,5.5);
		tested_Avg[count].x = x;
		tested_Avg[count].y = y;
		Circle(filtered,copyLocal,copyLocal,x,y);
		tested_Hough[count].x = x;
		tested_Hough[count].y = y;
		++count;
		char c=cvWaitKey(10);
  	}
	evaluation(tested_Hough,tested_Avg);
 	return 0;
}

