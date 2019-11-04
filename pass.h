int getMinimumOfNeighbours(int** tab, int wightOfImage, int heightOfImage, int posRow, int posCol);

int** tableCreating(int rows, int cols);

void createBinaryTable(int**& tab, cv::Mat img, int rows, int cols);

void numberCells(int**& tab, int rows, int cols);

void topDownPass(int**& tab, int rows, int cols);

void bottomUpPass(int**& tab, int rows, int cols);

void numberAreas(cv::Mat img, int** tab, int rows, int cols);