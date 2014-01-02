#include "stdafx.h"
#include "evaluation.h"
using namespace std;

int evalSize = 56;

double evaluation(point* tested){
	int discardCount = 0;
	double totalDistanceCount = 0;
	double distanceCount;
	ifstream fin("C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\norm.txt");
	point *norm = new point[evalSize];
	for(int i=0;i<evalSize;++i){
		fin>>norm[i].x>>norm[i].y;
		if(tested[i].x==-1){
			++discardCount;
			continue;
		}
		distanceCount = sqrt (double((norm[i].x-tested[i].x)*(norm[i].x-tested[i].x)+(norm[i].y-tested[i].y)*(norm[i].y-tested[i].y)));
		totalDistanceCount += distanceCount;
	}
	if(discardCount>20){
		return 100;
	}
	return (totalDistanceCount)/(evalSize-discardCount);
}


double compara(point* tested_Hough,point* tested_Avg){
	int discardCount = 0;
	double totalDistanceCount = 0;
	double distanceCount;
	ifstream fin("C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\norm.txt");
	ofstream fout("C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\result.txt");
	point *norm = new point[evalSize];
	for(int i=0;i<evalSize;++i){
		fin>>norm[i].x>>norm[i].y;
		if(tested_Hough[i].x==-1||tested_Avg[i].x==-1){
			++discardCount;
			continue;
		}
		int tmp_x,tmp_y;
		if(tested_Hough[i].x==-1){
			tmp_x = tested_Avg[i].x;
			tmp_y = tested_Avg[i].y;
		}
		if(tested_Avg[i].x==-1){
			tmp_x = tested_Hough[i].x;
			tmp_y = tested_Hough[i].y;
		}
		if(tested_Hough[i].x!=-1&&tested_Avg[i].x!=-1){
			tmp_x = (tested_Avg[i].x+tested_Hough[i].x)/2;
			tmp_y = (tested_Avg[i].y+tested_Hough[i].y)/2;
		}
		distanceCount = sqrt (double((norm[i].x-tmp_x)*(norm[i].x-tmp_x)+(norm[i].y-tmp_y)*(norm[i].y-tmp_y)));
		double xx = sqrt (double((norm[i].x-tested_Avg[i].x)*(norm[i].x-tested_Avg[i].x)+(norm[i].y-tested_Avg[i].y)*(norm[i].y-tested_Avg[i].y)));
		double yy = sqrt (double((norm[i].x-tested_Hough[i].x)*(norm[i].x-tested_Hough[i].x)+(norm[i].y-tested_Hough[i].y)*(norm[i].y-tested_Hough[i].y)));
		//totalDistanceCount += distanceCount;
		fout<<distanceCount<<'\t'<<xx<<'\t'<<yy<<endl;
	}
	//fout<<endl<<"averDistanceCount: "<<(totalDistanceCount)/(evalSize-discardCount);
	return (totalDistanceCount)/(evalSize-discardCount);
}


double evaluation(point* tested_Hough,point* tested_Avg){
	int discardCount = 0;
	double totalDistanceCount = 0;
	double distanceCount;
	ifstream fin("C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\norm.txt");
	ofstream fout("C:\\Users\\k\\Documents\\Visual Studio 2010\\Projects\\test3\\Debug\\result.txt");
	point *norm = new point[evalSize];
	for(int i=0;i<evalSize;++i){
		fin>>norm[i].x>>norm[i].y;
		if(tested_Hough[i].x==-1&&tested_Avg[i].x==-1){
			++discardCount;
			continue;
		}
		int tmp_x,tmp_y;
		if(tested_Hough[i].x==-1){
			tmp_x = tested_Avg[i].x;
			tmp_y = tested_Avg[i].y;
		}
		if(tested_Avg[i].x==-1){
			tmp_x = tested_Hough[i].x;
			tmp_y = tested_Hough[i].y;
		}
		if(tested_Hough[i].x!=-1&&tested_Avg[i].x!=-1){
			tmp_x = (tested_Avg[i].x+tested_Hough[i].x)/2;
			tmp_y = (tested_Avg[i].y+tested_Hough[i].y)/2;
		}
		distanceCount = sqrt (double((norm[i].x-tmp_x)*(norm[i].x-tmp_x)+(norm[i].y-tmp_y)*(norm[i].y-tmp_y)));
		totalDistanceCount += distanceCount;
		fout<<distanceCount<<endl;
	}
	fout<<endl<<"averDistanceCount: "<<(totalDistanceCount)/(evalSize-discardCount);
	return (totalDistanceCount)/(evalSize-discardCount);
}












