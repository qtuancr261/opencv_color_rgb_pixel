#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
void calChannel(const vector<int>& colorValue, int& countPixels)
{
	for (int i{}; i < 256; i++)
	{
		cout << left << setw(6) << "Value " << setw(3) << i << ": " << setw(4) << colorValue[i] << "| ";
		countPixels += colorValue[i];
		if (i % 8 == 0) cout << endl;
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	Mat input_img;
	input_img = imread(argv[1], IMREAD_COLOR);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return -1;
	}
	//--------------------------------------------------------------------------------------------
	vector<vector<Vec3b>> pixel(input_img.rows, vector<Vec3b>(input_img.cols));
	vector<int> redChannel(256, 0);
	vector<int> greenChannel(256, 0);
	vector<int> blueChannel(256, 0);
	int countPixels{};
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			pixel[i][j] = input_img.at<Vec3b>(i, j);
			blueChannel[(unsigned int)pixel[i][j][0]]++;
			greenChannel[(unsigned int)pixel[i][j][1]]++;
			redChannel[(unsigned int)pixel[i][j][2]]++;
		}
	cout << "Blue Channel: " << endl;
	calChannel(blueChannel, countPixels);
	cout << "Green Channel: " << endl;
	calChannel(greenChannel, countPixels);
	cout << "Red Channel" << endl;
	calChannel(redChannel, countPixels);
	cout << "Pixels: " << countPixels << endl;
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	waitKey();
	return 0;
}
