#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/world.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <iomanip>
#include "pass.h"
#include "gui.h"

//print info about project
void printInfo() {
	std::cout << "Mateusz Mizio" << std::endl;
	std::cout << "Seg 1" << std::endl;
	std::cout << "Segmentacja topdown, bottom-up" << std::endl;
	std::cout << "Nacisnij klawisz, aby zobaczyc obraz..." << std::endl;
}

//load binary image
cv::Mat loadBinaryImage() {
	cv::Mat img = cv::imread("image3.jpg");
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 100, 255, cv::THRESH_BINARY);
	return img;
}

//display image
void displayImage(cv::Mat img) {
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

//run program
void program()
{
	printInfo();
	system("pause");
	cv::Mat img = loadBinaryImage();
	int cols = img.size().width;
	int rows = img.size().height;
	int** tab;
	tab = tableCreating(rows, cols);
	
	createBinaryTable(tab, img, rows, cols);
	numberCells(tab, rows, cols);
	topDownPass(tab, rows, cols);
	bottomUpPass(tab, rows, cols);
	markAreas(img, tab, rows, cols);
	
	displayImage(img);
}
