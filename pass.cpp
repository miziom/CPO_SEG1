#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/world.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <iomanip>
#include "pass.h"


//method return minimum value from neighbours values
int getMinimumOfNeighbours(int** tab, int wightOfImage, int heightOfImage, int posRow, int posCol) {
	//create help table, size equals region of pixel
	int helpTab[9];
	//fill with -1
	for (int col = 0; col < 9; col++) {
		helpTab[col] = -1;
	}
	//set help position
	int helpTabPosCol = 0;
	int helpWightOfImage = wightOfImage - 1;
	int helpHeightOfImage = heightOfImage - 1;
	int helpPosRowMin = posRow - 1;
	int helpPosRowMax = posRow + 1;
	int helpPosColMin = posCol - 1;
	int helpPosColMax = posCol + 1;

	//correction of position if there are out of image
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
	//copy value from input table to helpTable with neighbours values
	for (int row = helpPosRowMin; row <= helpPosRowMax; row++) {
		for (int col = helpPosColMin; col <= helpPosColMax; col++) {
			helpTab[helpTabPosCol] = tab[row][col];
			helpTabPosCol++;
		}
	}
	int min = -2;
	//set last value of helTable which is not 0 or -1
	for (int col = 0; col < 9; col++) {
		if (!(helpTab[col] == 0 || helpTab[col] == -1)) {
			min = helpTab[col];
		}
	}
	//find minumum of region
	for (int col = 0; col < 9; col++) {
		if (helpTab[col] < min && helpTab[col] != -1 && helpTab[col] != 0) {
			min = helpTab[col];
		}
	}
	return min;
}

//create empty table
int** tableCreating(int rows, int cols) {

	int** tab = new int* [rows];

	for (int i = 0; i < rows; i++) {
		tab[i] = new int[cols];
	}
	return tab;
}

//create table with 0 and 1 depended on image pixel (black -> 1, white -> 0)
void createBinaryTable(int**& tab, cv::Mat img, int rows, int cols) {

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

}

//cells with 1 get own number
void numberCells(int**& tab, int rows, int cols) {

	int counter = 1;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (tab[row][col] == 1) {
				tab[row][col] = counter;
				counter++;
			}
		}
	}

}

//TopDown pass
void topDownPass(int**& tab, int rows, int cols) {

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (tab[row][col] != 0) {
				tab[row][col] = getMinimumOfNeighbours(tab, cols, rows, row, col);
			}
		}
	}
}

//BottomUp pass
void bottomUpPass(int**& tab, int rows, int cols) {

	for (int row = rows - 1; row >= 0; row--) {
		for (int col = cols - 1; col >= 0; col--) {
			if (tab[row][col] != 0) {
				tab[row][col] = getMinimumOfNeighbours(tab, cols, rows, row, col);
			}
		}
	}
}

//change numbers from each "value" to "guard+1" in table
void changeNumber(int** &table, int rows, int cols, int value, int guard) {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (table[row][col] == value) {
				table[row][col] = guard+1;
			}
		}
	}
}

//number fields from 1 to X (same value for whole field)
void reNumberTable(int**& table, int rows, int cols) {
	int guard = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (table[row][col] > guard) {
				changeNumber(table, rows, cols, table[row][col], guard);
				guard++;
			}
		}
	}
}

//mark areas with grayscale value
void markAreas(cv::Mat img, int** tab, int rows, int cols) {
	reNumberTable(tab, rows, cols);
	int guard = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (tab[row][col] != 0) {
				img.at<unsigned char>(row, col) = (tab[row][col] * 15);
			} 
		}
	}
}