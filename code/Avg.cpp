#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <sstream>
using namespace cv;

int Mymin = 0;

int findSmall(int *arr, int f, int h)
{
	int step = 5;
	int count = 0;
	int tmp = arr[h];
	if (f<h) {
		for (int i=h; i>=f; i--) {
			if (arr[i] >= Mymin) { count=0; tmp = arr[i]; }
			if (arr[i] <= tmp) { count = 0; tmp = arr[i]; }
			else {
				count++;
				if (count >= step)
				return i;	
			}
		
		}
	}
	else {
		tmp = arr[h];
		for (int i=h; i<=f; i++) {
			if (arr[i] >= Mymin) { count=0; tmp = arr[i]; }
			if (arr[i]<=tmp) { count = 0; tmp = arr[i]; }
			else {
				count++;
				if (count>=step)
				return i;
			
			}
		}
	}
	
	return -1;
}

void averagePoint(const Mat& img_in, const Mat& img_draw, Mat& img_re, int &x, int &y)
{
	int sum;
	//std::cout << "aver " << img_in.step[1] << '\n';
	uchar *imgData =(uchar*) img_in.data;
	x=y=0;
	std::cout << img_in.rows << " " << img_in.cols << '\n';
	Mat img_tmpr = img_in.clone();
	uchar *imgData_tmpr = (uchar*)img_tmpr.data;

	//namedWindow("TTK3", 0);
	//imshow("TTK3", img_tmpr);
	
	bool *col_f = new bool[img_in.cols];
	for (int i=0; i<img_in.cols; i++) col_f[i] = false;
	
	int col_count = 0;
	int max;
	max = img_in.rows/5.5;
	Mymin = img_in.rows/7;
	//5.5
	
	int tmp = 0;
	int bign = -1;
	int *col_num = new int[img_in.cols];
	
	for (int n=0; n<img_in.cols; n++) {
		col_num[n] = 0;
		for (int m=0; m<img_in.rows; m++) {
			int slot = m*img_in.cols+n;
			if ((int)imgData[slot]==0) {
				col_num[n]++;
			}
		}
		if (col_num[n] > tmp && col_num[n] < img_in.rows) { tmp = col_num[n]; bign = n; }
	}
	/*
	std::cout << "bign " << bign << '\n';
	int tl = findSmall(col_num, 1, bign);
	int th = findSmall(col_num, img_in.cols-1, bign);
	std::cout << "tl " << tl << " th " << th << '\n';
	*/
	//max = (tmp*3)/4;
	//std::cout << "max "<< max << '\n';
	//max = 0;
	
	for (int n=0; n<img_in.cols; n++) {
		if (col_num[n]>max && col_num[n] < img_in.rows) col_f[n] = true;
		//std:: cout << n << " " << col_num[n] << '\n'; 
		//if (n>=tl && n<=th) col_f[n] = true;
	}
		
	//for (int i=0; i<img_in.cols; i++) col_f[i] = true;
	
	for (int n=0; n<img_in.cols; n++) {
		for (int m=0; m<img_in.rows; m++) {
			int slot = m*img_in.step[0]+n*img_in.step[1];

			if (col_f[n]) {
				if ((int)imgData[slot] == 0) {
					if (m==0 || m==img_in.rows-1) {
						imgData_tmpr[slot] = 255;
					}
					else {
						x += n;
						y += m;
					}
				}
			}
			else {
				imgData_tmpr[slot]=255;
			}
		}
	
	}
		

	sum = img_tmpr.rows*img_tmpr.cols-countNonZero(img_tmpr);
	img_re = img_draw.clone();
	if (sum == 0) { 
	//std::cout <<"error div o!\n"; 
	x=-1;
	return;}
	x = x / sum;
	y = y / sum;
	
	Point ce(x, y);
	circle(img_re, ce, 3, Scalar(0,255,0));
	Point re(99 ,44);
	circle(img_re, re, 3, Scalar(0,0,255));
	
	namedWindow("TTK1", 0);
	imshow("TTK1", img_tmpr);
	imwrite( "tmpr.jpg",img_tmpr);
	namedWindow("TTK2", 0);
	imshow("TTK2", img_re);
	imwrite("re.jpg", img_re );
	waitKey();

}

