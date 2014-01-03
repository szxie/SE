#include "stdafx.h"
#include "HSV.h"
#include "Circle.h"
#include "Avg.h"
#include "corner.h"
#include "evaluation.h"

using namespace cv;

const int wastedFrameCnt = 0;
extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;
extern int MinH;
extern int MinS;
extern int MinV;
extern int MaxH;
extern int MaxS;
extern int MaxV;
extern int evalSize;


int recordVideo(char* outputVideoPath)
{
	const char WindName_video[] = "video";
 	Mat frame;
	namedWindow( WindName_video, CV_WINDOW_NORMAL );
  	CvCapture* capture = cvCreateCameraCapture(-1);
	frame = cvQueryFrame( capture );
	VideoWriter writer(outputVideoPath, CV_FOURCC('M', 'J', 'P', 'G'), 5, frame.size());

    while( true ) {
    	frame = cvQueryFrame( capture );
		flip(frame, frame, 1);
		imshow(WindName_video, frame);
		writer<<frame;
      	char c=cvWaitKey(1000/24);
      	if(c==27)break;
  	}
 	return 0;
}

int videoToImages(char* inputVideoPath, char* outputImagesPath)
{
 	Mat frame;
	int count = 0;
	VideoCapture reader(inputVideoPath);

    while( reader.read(frame) ) {

		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);

		std::stringstream strStream;  
		++count;
		strStream<<count;
		string s = strStream.str();  
		imwrite(outputImagesPath+s+".jpg",local);
		char c=cvWaitKey(5);
		if(c==27)
			return 0;
  	}
	return 0;
}

int loadVideoCutLocal(char* inputVideoPath)
{
	const char WindName_video[] = "video";
 	Mat frame;
	int count = 0;
	namedWindow( WindName_video, CV_WINDOW_NORMAL );
	VideoCapture reader(inputVideoPath);

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
		imshow(WindName_video, local);
		cvWaitKey(1000/5);
  	}
 	return 0;
}

int printLocalFrame(char* inputVideoPath)
{
	const char WindName_local[] = "local";
	const char WindName_filtered[] = "filtered";
 	Mat frame, binary;
	int count = 1;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(inputVideoPath);

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		bool flag = 1;
		
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		while(1){
			Mat filtered;
			HSV(local,local,filtered);

			inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
			int nonZeroCount = countNonZero(binary);
			int x,y;
			bitwise_not(binary,binary);
			averagePoint(binary,filtered,filtered,x,y);
			//Circle(filtered,filtered,filtered,x,y);
			if(x==-1){
				flag = 0;
			}
			else{
				flag = 1;
			}
			
			//Circle(filtered,frame,frame,x,y);

			imshow(WindName_filtered, filtered);
			
			char c=cvWaitKey(10);
			if(c=='a'||c=='A')
				break;
			if(c==27)
				return 0;
		}
		if(flag){
			++count;
		}
		std::cout<<count<<std::endl;
  	}
 	return 0;
}

int printGlobalVideo(char* inputVideoPath)
{
	const char WindName_local[] = "local";
	const char WindName_filtered[] = "filtered";
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(inputVideoPath);

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		++count;
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		while(1){
			Mat filtered;
			HSV(local,local,filtered);

			inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
			int nonZeroCount = countNonZero(binary);
			//Circle(filtered,filtered,filtered,nonZeroCount);
			int x,y;
			//averagePoint(binary,frame,frame,x,y,5.5);
			Circle(filtered,frame,frame,x,y);

			imshow(WindName_filtered, frame);

			char c=cvWaitKey(10);
			break;
			/*if(c=='a'||c=='A')
				break;
			if(c==27)
				return 0;*/
		}
		char c=cvWaitKey(10);
		if(c==27)
			return 0;
  	}
	return 0;
}

int basicEvaluation(char* inputVideoPath)
{
	const char WindName_local[] = "local";
	const char WindName_filtered[] = "filtered";
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(inputVideoPath);
	point *tested = new point[evalSize];

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
		Circle(filtered,copyLocal,copyLocal,x,y);
		tested[count].x = x;
		tested[count].y = y;
		++count;
		char c=cvWaitKey(10);
  	}
	evaluation(tested);
 	return 0;
}

int hybridEvaluation(char* inputVideoPath)
{
	const char WindName_local[] = "local";
	const char WindName_filtered[] = "filtered";
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(inputVideoPath);
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

int findOptimalPara(char* inputVideoPath)
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
			VideoCapture reader(inputVideoPath);
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

int findMultiOptimalParas(char* inputVideoPath)
{
	double optimal = 100;
	double result;
	double optimal_others = 0;
	double optimal_circle = 0;
	double optimal_divisor = 0;
 	Mat frame, binary;
	point *tested = new point[evalSize];
	
	for(double k=1;k<=10;++k){
		double divisor = 2.5+k*0.1;
	for(int i=4;i<10;++i){
		for(int j=1;j<8;++j){
			double fillRate_others = 0.1*j;
			double fillRate_circle = 0.1*i;

			int count = 0;
			VideoCapture reader(inputVideoPath);
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
				Circle(filtered,copyLocal,copyLocal,x,y,fillRate_others,fillRate_circle,divisor);
				tested[count].x = x;
				tested[count].y = y;
				++count;
			}
			result = evaluation(tested);
			if (result<optimal){
				optimal = result;
				optimal_others = fillRate_others;
				optimal_circle = fillRate_circle;
				optimal_divisor = divisor;
			}
		}
	}
	}
	std::cout<<optimal<<std::endl<<optimal_others<<std::endl<<optimal_circle<<std::endl<<optimal_divisor;
 	return 0;
}

int finalDemo(char* inputVideoPath, char* outputVideoPath)
{
	const char WindName_local[] = "local";
	const char WindName_filtered[] = "filtered";
 	Mat frame, binary;
	int count = 0;
	namedWindow( WindName_local, 0 );
	namedWindow( WindName_filtered, 0 );
	VideoCapture reader(inputVideoPath);
	reader.read(frame);
	VideoWriter writer(outputVideoPath, CV_FOURCC('M', 'J', 'P', 'G'), 20, frame.size());

    while( reader.read(frame) ) {
		//imshow(WindName, frame);
		++count;
		Mat print = frame.clone();
		if(count<wastedFrameCnt){
			continue;
		}
		Size sizeFrame = frame.size();
		Range colRange(sizeFrame.width*Local_xMin, sizeFrame.width*Local_xMax);
		Range rowRange(sizeFrame.height*Local_yMin, sizeFrame.height*Local_yMax);
		Mat local(frame,rowRange,colRange);
		imshow(WindName_local, local);

		while(1){
			Mat filtered;

			MaxV = 40;
			HSV(local,local,filtered);
			find_corner(filtered,frame,print);

			MaxV = 22;
			HSV(local,local,filtered);
			inRange(filtered, Scalar(MinH,MinS,MinV), Scalar(MaxH,MaxS,MaxV), binary);
			bitwise_not(binary,binary);
			int nonZeroCount = countNonZero(binary);
			//Circle(filtered,filtered,filtered,nonZeroCount);
			int Avg_x,Avg_y,Hough_x,Hough_y,hybrid_x,hybrid_y;
			averagePoint(binary,frame,frame,Avg_x,Avg_y);
			Circle(filtered,frame,frame,Hough_x,Hough_y);
			if(Avg_x==-1 && Hough_x==-1){
				imshow(WindName_filtered, print);
				break;
			}
			if(Avg_x==-1){
				hybrid_x = Hough_x;
				hybrid_y = Hough_y;
			}
			if(Hough_x==-1){
				hybrid_x = Avg_x;
				hybrid_y = Avg_y;
			}
			if(Avg_x!=-1 && Hough_x!=-1){
				hybrid_x = (Hough_x+Avg_x)/2;
				hybrid_y = (Hough_y+Avg_y)/2;
			}

			Point center( hybrid_x+print.size().width*Local_xMin, hybrid_y+print.size().height*Local_yMin);
			circle( print, center, 3, Scalar(0,0,255), -1, 8, 0 );
			imshow(WindName_filtered, print);

			char c=cvWaitKey(5);
			break;
			/*if(c=='a'||c=='A')
				break;
			if(c==27)
				return 0;*/
		}
		writer<<print;
		char c=cvWaitKey(5);
		if(c==27)
			return 0;
  	}
	return 0;
}
