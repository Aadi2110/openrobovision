//
// ������������ ������������ OpenCV ����� ��������� C++
//
// http://robocraft.ru
//

#include "orv/orv.h"

#include "opencv2/opencv.hpp"

int main(int argc, char* argv[])
{
	cv::VideoCapture cap(0); // ������� ������ ��-���������
	if(!cap.isOpened())		 // �������?
	{
		std::cout<<"[!] Error: cant open camera!"<<std::endl;
		return -1;
	}
	cv::Mat gray;
	cv::Mat edges;
	cv::namedWindow("frame");
	cv::namedWindow("edges");
	while(1)
	{
		cv::Mat frame;
		// � VideoCapture ���������� �������� >> ,������� ����� ������������ ��� ���������� �����
		cap >> frame; // �������� ����� ����
		cv::imshow("frame", frame);		// ���������� ��������
		cv::cvtColor(frame, gray, CV_BGR2GRAY); // ������������ � �������� ������
		cv::GaussianBlur(gray, gray, cv::Size(7,7), 1.5, 1.5); // �������� (�������� ������)
		cv::Canny(gray, edges, 0, 30);	// �������� ������ �����
		cv::imshow("edges", edges);		// ���������� ��������
		int key = cv::waitKey(33);
		if(key == 27) //ESC
			break;
		else if(key == 13) // Enter
		{
			// �������� ���� � ����
			cv::imwrite("frame.jpg", frame);
			cv::imwrite("edges.jpg", edges);
			std::cout<<"[i] Saved."<<std::endl;
		}

	}
	// ������ ����� ������������� ����������� � ����������� VideoCapture
	return 0;
}
