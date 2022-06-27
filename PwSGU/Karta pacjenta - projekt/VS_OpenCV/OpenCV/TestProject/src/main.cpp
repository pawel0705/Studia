#include "pch.h"

int main()
{
	cv::VideoCapture vc;
	vc.open(0);
	cv::CascadeClassifier faceClassifier;
	faceClassifier.load("haarcascades/haarcascade_frontalface_default.xml");
	for (;;) {
		cv::Mat img;
		vc >> img;
		std::vector<cv::Rect> objects;
		faceClassifier.detectMultiScale(img, objects);
		cv::imshow("test", img);
		cv::waitKey(1);
		int i = 0, tlx, tly, brx, bry;
		for (auto it = objects.begin(); it != objects.end(); ++it, i++) {
			tlx = it->x;
			tly = it->y;
			brx = it->width;
			bry = it->height;
			std::cout << "[tlx, tly, brx, bry]=[" << tlx << "," << tly << "," << brx << "," << bry << "]\n";
		}
		std::cout << "============================\n";
	}

}