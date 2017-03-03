#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
void calChannel(const vector<int>& colorValue)
{
	for (int i{}; i < colorValue.size(); i++)
	{
		cout << left << setw(6) << "bin " << setw(3) << i << ": " << setw(6) << colorValue[i] << "| ";
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
	int numBin{};
	cout << "Nhap vao so luong bin: ";
	cin >> numBin;
	int binRange{ 256 / numBin };
	vector<vector<Vec3b>> pixel(input_img.rows, vector<Vec3b>(input_img.cols));
	vector<int> redChannel(numBin, 0);
	vector<int> greenChannel(numBin, 0);
	vector<int> blueChannel(numBin, 0);
	int countPixels{};
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			pixel[i][j] = input_img.at<Vec3b>(i, j);
			blueChannel[(unsigned int)(pixel[i][j][0] / binRange)]++;
			greenChannel[(unsigned int)(pixel[i][j][1] / binRange)]++;
			redChannel[(unsigned int)(pixel[i][j][2] / binRange)]++;
		}
	cout << "Blue Channel: " << endl;
	calChannel(blueChannel);
	cout << "Green Channel: " << endl;
	calChannel(greenChannel);
	cout << "Red Channel" << endl;
	calChannel(redChannel);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	waitKey();
	return 0;
}
