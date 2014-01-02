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
	double optimal = 100;
	double result;
	double optimal_others = 0;
	double optimal_circle = 0;
 	Mat frame, binary;
	point *tested = new point[evalSize];
	
	for(int i=4;i<10;++i){
		for(int j=0;j<8;++j){
			double fillRate_others = 0.1*j;
			double fillRate_circle = 0.1*i;

			int count = 0;
			VideoCapture reader(InputVideoPath);
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
				//averagePoint(binary,copyLocal,copyLocal,x,y);
				Circle(filtered,copyLocal,copyLocal,x,y,fillRate_others,fillRate_circle);
				tested[count].x = x;
				tested[count].y = y;
				++count;
			}
			result = evaluation(tested);
			if (result<optimal){
				optimal = result;
				optimal_others = fillRate_others;
				optimal_circle = fillRate_circle;
			}
		}
	}
	std::cout<<optimal<<std::endl<<optimal_others<<std::endl<<optimal_circle;
 	return 0;
}

