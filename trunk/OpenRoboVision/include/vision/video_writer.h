//
// OpenRoboVision
//
// object for writes frames to video-file
//
// ������ ��� ������ �����-������
//
//
// robocraft.ru
//

#ifndef _VIDEO_WRITER_H_
#define _VIDEO_WRITER_H_

#ifdef USE_OPENCV

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// �������� ���� ��� ������ �������� �� �����
#define VIDEOWRITER_CAPTURE_WINDOW_NAME "video write"
// ������� ��-���������
#define VIDEOWRITER_DEFAULT_FPS 15
// ����� ��-���������
#define VIDEOWRITER_DEFAULT_CODEC CV_FOURCC('X','V','I','D')
//
// 4-��������� ��� ������ ��� ��������� �����:
//
// CV_FOURCC('X','V','I','D')	 = ����� XviD
// CV_FOURCC('P','I','M','1')    = MPEG-1
// CV_FOURCC('M','J','P','G')    = motion-jpeg  (does not work well)
// CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 
// CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 
// CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 
// CV_FOURCC('U', '2', '6', '3') = H263 
// CV_FOURCC('I', '2', '6', '3') = H263I 
// CV_FOURCC('F', 'L', 'V', '1') = FLV1 

class Videowriter
{
	CvVideoWriter *writer;
	
	const char* window_name; // �������� ���� ��� ����������� ��������
	bool show_capture; // ���� ������������ ���������� �������� ��� ���
public:
	Videowriter();
	Videowriter(char* filename);
	Videowriter(char* filename, int width, int height);
	Videowriter(char* filename, CvSize size, double fps=VIDEOWRITER_DEFAULT_FPS, int codec=VIDEOWRITER_DEFAULT_CODEC, int is_color=true);
	~Videowriter();

	// �������������
	void setup();

	// �������� ���� � ����
	void write(IplImage* image);
	// ��������� ������
	void end();

	// ����� ���������� �� ����������� ��������
	void setShowCapture(bool show=false);

	CvSize size;	// ������ �����
	double fps;		// �������
	int codec;		// ����� (fourcc)
	char* filename;	// �������� �����
	bool isColor;	// ������� ��������

private:
};

#endif //#ifdef USE_OPENCV

#endif //#ifndef _VIDEO_WRITER_H_
