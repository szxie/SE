#ifndef ENTRANCE_H
#define ENTRANCE_H

int recordVideo(char* outputVideoPath);
int videoToImages(char* inputVideoPath, char* outputImagesPath);
int loadVideoCutLocal(char* inputVideoPath);
int printLocalFrame(char* inputVideoPath);
int printGlobalVideo(char* inputVideoPath);
int basicEvaluation(char* inputVideoPath);
int hybridEvaluation(char* inputVideoPath);
int findOptimalPara(char* inputVideoPath);
int findMultiOptimalParas(char* inputVideoPath);
int finalDemo(char* inputVideoPath, char* outputVideoPath);

#endif