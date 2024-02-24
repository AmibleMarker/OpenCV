#include<iostream>
#include<opencv2/opencv.hpp>
#include"Energy.h"
#include<queue>

using namespace std;
using namespace cv;

vector<vector<Point>> contours;

bool flag = false;

int ArmorDescribtor::target_block()
{
	double maximum = 0;
	int i;
	for (i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) > maximum)
		{
			maximum = contourArea(contours[i]);
		}
	}

	queue<int> no_pass;
	maximum = maximum / 5;
	for (i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) < maximum)
		{
			no_pass.push(i);
		}
	}

	double minmum = 0;
	int target = -1, cnt = no_pass.size();

	for (i = 0; i < contours.size(); i++)
	{
		if (!no_pass.empty() && no_pass.front() == i)
		{
			no_pass.pop();
			continue;
		}
		if (!minmum)
		{
			minmum = contourArea(contours[i]);
			target = i;
		}
		else if (minmum > contourArea(contours[i]))
		{
			minmum = contourArea(contours[i]);
			target = i;
		}
	}

	if (maximum * 5 - minmum < minmum && contours.size() - cnt == 5) return -1;
	return target;
}

void ArmorDescribtor::edge_search(Mat& image_copy, Mat& image)
{
	if (flag) return;
	Mat img;
	image_copy.copyTo(img);
	//system("cls");

	Mat canny;
	Canny(img, canny, 100, 200, 7, false);
	//imshow("canny", canny);

	findContours(canny, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	int i = target_block();
	if (i == -1)
	{
		flag = true;
		return;
	}

	RotatedRect rect = minAreaRect(contours[i]);
	Point2f center = rect.center;
	circle(image, center, 2, Scalar(0, 255, 0), 2, 8, 0);
	
	RotatedRect result = minAreaRect(contours[i]);
	Point2f point[4];
	result.points(point);
	for (int j = 0; j < 4; j++)
	{
		if (j == 3)
		{
			line(image, point[3], point[0], Scalar(0, 255, 0), 2, 8, 0);
			break;
		}
		line(image, point[j], point[j + 1], Scalar(0, 255, 0), 2, 8, 0);
	}

	//imshow("img", img);
}

void ArmorDescribtor::area_filt(Mat& img, int model)
{
	Mat color[3];

	split(img, color);
	if (model == 1) img = color[0] - color[2];
	else img = color[2] - color[0];
	threshold(img, img, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat mask = Mat::zeros(img.rows + 2, img.cols + 2, CV_8UC1);
	floodFill(img, mask, Point(2, 2), 255);

	Mat kernel = getStructuringElement(0, Size(9, 9));
	morphologyEx(img, img, MORPH_OPEN, kernel);
}

