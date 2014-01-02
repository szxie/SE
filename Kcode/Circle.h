#ifndef CIRCLE_H
#define CIRCLE_H

//src1 计算依据，src2 输出依据，srcorin 输出
void Circle(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &srcorin, int &x, int &y, double MaxfillRate_others=0.7, double MinfillRate_circle =0.7, double divisor = 2.6);

#endif
