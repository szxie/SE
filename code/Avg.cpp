#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include <sstream>
using namespace cv;

void averagePoint(const Mat& img_in, const Mat& img_draw, Mat& img_re, int &x, int &y)
{
	int sum;
	//std::cout << sum << '\n';
	uchar *imgData =(uchar*) img_in.data;
	x = 0;
	y = 0;
	std::cout << img_in.rows << " " << img_in.cols << '\n';
	Mat img_tmpr = img_in.clone();
	uchar *imgData_tmpr = (uchar*)img_tmpr.data;

	bool col_f[img_in.cols];
	for (int i=0; i<img_in.cols; i++) col_f[i] = false;
	
	int col_count = 0;
	int max=img_in.rows/4;
	
	
	for (int n=0; n<img_in.cols; n++) {
		col_count = 0;
		for (int m=0; m<img_in.rows; m++) {
			int slot = m*img_in.cols+n;
			if ((int)imgData[slot]==0) {
				col_count++;
			}
		}
		if (col_count > max)
			col_f[n]=true;
	}
	
	//for (int i=0; i<img_in.cols; i++) col_f[i] = true;
	
	for (int n=0; n<img_in.cols; n++) {
		for (int m=0; m<img_in.rows; m++) {
			int slot = m*img_in.step[0]+n*img_in.step[1];
			if (col_f[n]) {
				if ((int)imgData[slot] == 0) {
					x += n;
					y += m;
				}
			}
			else {
				imgData_tmpr[slot]=255;
			}
		}
	
	}
		

	sum = img_tmpr.rows*img_tmpr.cols-countNonZero(img_tmpr);
	if (sum == 0) { std::cout <<"error /o!\n"; exit(1);}
	x = x / sum;
	y = y / sum;
	img_re = img_draw.clone();
	
	Point ce(x, y);
	circle(img_re, ce, 2, Scalar(0,255,0));
	/*
	namedWindow("TTK1", 1);
	imshow("TTK1", img_tmpr);
	namedWindow("TTK2", 1);
	imshow("TTK2", img_re);
	*/
	//waitKey();
}

