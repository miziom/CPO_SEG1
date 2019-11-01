// Seg1Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/world.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

int getMinimumOfNeighbours(int **tab, int wightOfImage, int heightOfImage, int posRow, int posCol) {

	int helpTab[9];
		for (int col = 0; col < 9; col++) {
			helpTab[col] = -1;
		}
	int helpTabPosCol = 0;
	int helpWightOfImage = wightOfImage - 1;
	int helpHeightOfImage = heightOfImage -1;
	int helpPosRowMin = posRow - 1;
	int helpPosRowMax = posRow + 1;
	int helpPosColMin = posCol - 1;
	int helpPosColMax = posCol + 1;
	
	if (helpPosRowMin < 0) {
		helpPosRowMin = 0;
	}
	if (helpPosColMin < 0) {
		helpPosColMin = 0;
	}
	if (helpPosRowMax > helpHeightOfImage) {
		helpPosRowMax = helpHeightOfImage;
	}
	if (helpPosColMax > helpWightOfImage) {
		helpPosColMax = helpWightOfImage;
	}
	
	for (int row = helpPosRowMin; row <= helpPosRowMax; row++) {
		for (int col = helpPosColMin; col <= helpPosColMax; col++) {
			helpTab[helpTabPosCol] = tab[row][col];
			helpTabPosCol++;
		}
	}
	int min = -2;
	for (int col = 0; col < 9; col++) {
		if (helpTab[col] == 0 || helpTab[col] == -1) {
			
		}
		else {
			min = helpTab[col];
		}
	}
	
	for (int col = 0; col < 9; col++) {
		if (helpTab[col] < min && helpTab[col] != -1 && helpTab[col] != 0) {
			min = helpTab[col];
		}
	}
	return min;
}



int main()
{
	//int** tab1;
	//tab1 = new int* [5];

	//for (int i = 0; i < 5; i++) {
	//	tab1[i] = new int[5];
	//}
	//int a = 0;
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		tab1[i][j] = a;
	//		a++;
	//	}
	//}
	//int min = getMinimumOfNeighbours(tab1, 5, 5, 0, 1);
	//min = getMinimumOfNeighbours(tab1, 5, 5, 1, 1);





	int** tab;
	Mat img = imread("image2.jpg");
	cv::resize(img, img, img.size() );
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::threshold(img, img, 100, 255, cv::THRESH_BINARY);

	int cols = img.size().width;
	int rows = img.size().height;

	tab = new int* [rows];

	for (int i = 0; i < rows; i++) {
		tab[i] = new int[cols];
	}

	//create table with 0 and 1 depended on image pixel (black -> 1, white -> 0)
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (img.at<unsigned char>(row, col) == 255) {
				tab[row][col] = 0;
			}
			else
			{
				tab[row][col] = 1;
			}
		}
	}

	//cells with 1 get own number
	int counter = 1;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (tab[row][col] == 1) {
				tab[row][col] = counter;
				counter++;
			}
		}
	}

	//TopDown pass
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (tab[row][col] != 0) {
				tab[row][col] = getMinimumOfNeighbours(tab, cols, rows, row, col);
			}
		}
	}

	//BottomUp pass
	for (int row = rows - 1; row >= 0; row--) {
		for (int col = cols - 1; col >= 0; col--) {
			if (tab[row][col] != 0) {
				tab[row][col] = getMinimumOfNeighbours(tab, cols, rows, row, col);
			}
		}
	}


	cv::cvtColor(img, img, cv::COLOR_BGRA2RGBA);
	int fieldNumber = 1;
	int counterforNumber = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (tab[row][col] > counterforNumber) {
				cv::putText(img, //target image
					std::to_string(fieldNumber), //text
					cv::Point(col, row), //top-left position
					cv::FONT_HERSHEY_DUPLEX,
					0.5,
					CV_RGB(0, 255, 0), //font color
					1);
				//std::cout << fieldNumber << endl;
				counterforNumber = tab[row][col];
				fieldNumber++;
			}
		}
	}



	//for (int i = 0; i < rows; i++) {
	//	for (int j = 0; j < cols; j++) {
	//		std::cout << std::setw(4) << std::right << tab[i][j];
	//	}
	//	std::cout << endl;
	//}

	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);
	destroyAllWindows();

	//zwolnienie pamieci dla tabeli
	for (int i = 0; i < rows; i++) {
		delete[] tab[i];
	}
	delete[] * tab;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
