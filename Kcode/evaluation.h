#ifndef EVAL_H
#define EVAL_H

struct point{
	double x;
	double y;
};

double evaluation(point* tested);
double evaluation(point* tested_Hough,point* tested_Avg);
double compara(point* tested_Hough,point* tested_Avg);

#endif