#include "pch.h"
#include "OCVWrapper.h"
#include <string>
cv::CascadeClassifier faceClassifier;

unsigned  char* matToByte(cv::Mat  mat) {
	return  mat.data;
}

cv::Mat  byteToMat(long  long  length, int width, int  height, unsigned  char* data, int  type = CV_8UC3)
{
	cv::Mat  ImMat = cv::Mat(height, width, type, data);
	cv::flip(ImMat, ImMat, -1);
	return  ImMat;
}

void detectFace(long long length, int width, int  height, unsigned  char* data, float& tlx, float& tly, float& brx, float& bry)
{
	cv::Mat  img = byteToMat(length, width, height, data, CV_8UC3);
	std::vector <cv::Rect > objects;
	faceClassifier.detectMultiScale(img, objects);
	int i = 0;
	for (auto it = objects.begin(); it != objects.end(); ++it, i++)
	{
		tlx = it->x;
		tly = it->y;
		brx = it->width;
		bry = it->height;
	}
}

void loadClassifier(const char* fileName)
{
	faceClassifier.load(fileName);
}