#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/world.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <iomanip>
#include "pass.h"

using namespace std;
using namespace cv;



int main()
{
	Mat img = imread("image3.jpg");
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 100, 255, cv::THRESH_BINARY);

	int cols = img.size().width;
	int rows = img.size().height;
	int** tab;
	
	tab = tableCreating(rows, cols);
	createBinaryTable(tab, img, rows, cols);
	numberCells(tab, rows, cols);
	topDownPass(tab, rows, cols);
	bottomUpPass(tab, rows, cols);
	numberAreas(img, tab, rows, cols);

	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
