//
// OpenRoboVision
//
// object for get frames from video-file
//
// ������ ��� ������ �����-������
//
//
// robocraft.ru
//

#ifndef _VIDEO_READER_H_
#define _VIDEO_READER_H_

#ifdef USE_OPENCV

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// �������� ���� ��� ������ �������� �� �����
#define VIDEOREADER_CAPTURE_WINDOW_NAME "video read"

class Videoreader
{
	CvCapture* capture;
	IplImage* frame;
	const char* window_name; // �������� ���� ��� ����������� ��������
	bool show_capture; // ���� ������������ ���������� �������� ��� ���
public:
	Videoreader();
	Videoreader(char* filename);
	Videoreader(char* filename, int width, int height);
	~Videoreader();

	// �������������
	void setup();
	// �������� ��������� ����
	void update();
	// ���������� ���� �� �����
	IplImage* getFrame() {return frame;}

	// ����� ���������� �� ����������� ��������
	void setShowCapture(bool show=false);

	// �������� �����
	char* filename;

private:
};

#endif //#ifdef USE_OPENCV

#endif //#ifndef _VIDEO_READER_H_
