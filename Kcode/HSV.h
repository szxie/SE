#ifndef HSV_H
#define HSV_H

//img 原图，img_edge 修改依据，img_re 输出
void HSV(const cv::Mat &img, const cv::Mat &toBeFiltered, cv::Mat &img_re);
bool isOutOfBound(int slot, const cv::Mat &img_HSV);
bool isBlank(uchar* data,int slot);

#endif
