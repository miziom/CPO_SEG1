int** tableCreating(int rows, int cols);
void createBinaryTable(int**& tab, cv::Mat img, int rows, int cols);
void numberCells(int**& tab, int rows, int cols);
void topDownPass(int**& tab, int rows, int cols);
void bottomUpPass(int**& tab, int rows, int cols);
void markAreas(cv::Mat img, int** tab, int rows, int cols);