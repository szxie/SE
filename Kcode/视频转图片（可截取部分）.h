#include "stdafx.h"
using namespace cv;

const char* InputVideoPath = "C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\evaluation.avi";
const char* OutputImagePath = "F:\\eye_images\\";

extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;

int main()
{
 	Mat frame;
	int count = 0;
	VideoCapture reader(InputVideoPath);



    while( reader.read(frame) ) {

		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);

		std::stringstream strStream;  
		++count;
		strStream<<count;
		string s = strStream.str();  
		imwrite(OutputImagePath+s+".jpg",local);
		char c=cvWaitKey(5);
		if(c==27)
			return 0;
  	}
	return 0;
}



