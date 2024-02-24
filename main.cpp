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
	cout << "ѡ�������������ͣ�1 ͼ��  2 ��Ƶ\n";
	cin >> m;
	cout << "ѡ��ʶ�����ͣ�1 ��ɫ  2 ��ɫ\n";
	cin >> n;
	if (m == 1)
	{
		Mat image = imread("D:/wind/wind5.jpg");
		if (image.empty())
		{
			cout << "ͼ���ʧ��" << endl;
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
			cout << "�ļ���ʧ��" << endl;
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

