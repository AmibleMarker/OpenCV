#include<iostream>
#include<opencv2/opencv.hpp>
#include"Energy.h"
#include<opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;

ArmorDescribtor change;

int main()
{
	int m, n;
	cout << "选择输入数据类型：1 图像  2 视频\n";
	cin >> m;
	cout << "选择识别类型：1 蓝色  2 红色\n";
	cin >> n;
	if (m == 1)
	{
		Mat image = imread("D:/wind/wind5.jpg");
		if (image.empty())
		{
			cout << "图像打开失败" << endl;
			return -1;
		}
		Mat image_copy;
		GaussianBlur(image, image_copy, Size(3, 3), 10, 20);
		change.area_filt(image_copy, n);
		change.edge_search(image_copy, image);
		imshow("image", image);
	}
	else
	{
		VideoCapture video("D:/wind/wind.mp4");
		//system("color F0");
		if (!video.isOpened())
		{
			cout << "文件打开失败" << endl;
			return -1;
		}


		while (1)
		{
			Mat frame, frame_copy;
			video >> frame;
			if (frame.empty()) break;
			GaussianBlur(frame, frame_copy, Size(3, 3), 10, 20);
			change.area_filt(frame_copy, n);
			change.edge_search(frame_copy, frame);
			imshow("image", frame);
			waitKey(1000 / video.get(CAP_PROP_FPS));
		}
	}

	waitKey(0);
	return 0;
}

