#pragma once

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

class ArmorDescribtor
{
	public:
		void edge_search(Mat &image1, Mat& image2);
		void area_filt(Mat& image, int model);
		int target_block(void);
};
