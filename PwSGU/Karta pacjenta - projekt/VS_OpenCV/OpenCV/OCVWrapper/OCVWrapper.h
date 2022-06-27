#pragma once
#ifdef TESTFUNCDLL_EXPORT
	#define TESTFUNCDLL_API __declspec(dllexport)
#else
	#define TESTFUNCDLL_API __declspec(dllimport)
#endif

#include <opencv2/opencv.hpp>
extern "C" {
	cv::Mat  byteToMat(long  long  length, int width, int height, unsigned  char* data, int  type);
	unsigned  char* matToByte(cv::Mat  mat);
	TESTFUNCDLL_API  void  detectFace(long  long  length, int width, int  height, unsigned  char* data, float& tlx, float& tly, float& brx, float& bry);
	TESTFUNCDLL_API  void  loadClassifier(const char* fileName);
}