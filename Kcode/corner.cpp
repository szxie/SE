#include "stdafx.h"
#include "HSV.h"
using namespace cv;

extern double Local_xMin;
extern double Local_xMax;
extern double Local_yMin;
extern double Local_yMax;

void find_corner(const Mat &img1, const Mat &img2, Mat &img)
{
	img = img2.clone();
	int rightMost_x=0,leftMost_x=10000,rightMost_y,leftMost_y;
	for (int i=0; i<=img1.rows-1; i++) {
		for (int j=img1.cols-1; j>=0; j--) {
			int slot = i*img1.step[0]+j*img1.step[1];
			if(!isBlank(img1.data,slot))
			{
				if(j>rightMost_x){rightMost_x = j;rightMost_y = i;}
				if(j<leftMost_x){leftMost_x = j;leftMost_y = i;}
			}
		}
	}
	Point centerpoint1(rightMost_x+img2.size().width*Local_xMin, rightMost_y+img2.size().height*Local_yMin);
	Point centerpoint2(leftMost_x+img2.size().width*Local_xMin, leftMost_y+img2.size().height*Local_yMin);
	circle( img, centerpoint1 ,5 , Scalar(0,255,0),-1, 8, 0 );
	circle( img, centerpoint2 ,5 , Scalar(0,255,0),-1, 8, 0 );
	//std::cout<<rightMost_x<<'\t'<<rightMost_y<<std::endl;
}
