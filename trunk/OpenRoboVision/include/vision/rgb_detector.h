//
// OpenRoboVision
//
// for detect objects by RGB-color
//
// ��� �������������� �� RGB-�����
//
//
// robocraft.ru
//

#ifndef _RGBDETECTOR_H_
#define _RGBDETECTOR_H_

#ifdef USE_OPENCV

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

// ���������� RGB-����
#define RGBDETECTOR_SHOW_RGB 0
// ���������� ����������� ����� ���������� ��������������
#define RGBDETECTOR_SHOW_RGB_THRESHOLD 0
// ���������� ����������� ����� �������� ����
#define RGBDETECTOR_SHOW_RGB_AND 0
// �������� ����������� ����� ���������������� ��������������
#define RGBDETECTOR_SHOW_RGB_MORTH 0

class RGBDetector
{
	IplImage* img;
	IplImage* r_plane;
	IplImage* g_plane;
	IplImage* b_plane;
	IplImage* and_img;
	IplImage* temp;
	IplImage* morth;
	IplConvKernel* Kern;

public:
	RGBDetector();
	~RGBDetector();

	// �������������
	void setup();
	void update();
	void make();

	// �������� ����� ���� ������� �� �����������
	bool getCenter(IplImage* image, CvPoint2D32f &center, float threshold=5);

	IplImage* result; // ��������� �� ����������� � ����������� ��������

	int Rmin;
	int Rmax;

	int Gmin;
	int Gmax;

	int Bmin;
	int Bmax;

	// ����, ����������� ������������ �� ��������������� ��������������
	bool useMorthology;

private:
	// ��������� ������ ��� �����������
	void initImages(IplImage* image);
	// ������������ �����������
	void releaseImages();
	
};

#endif //#ifdef USE_OPENCV

#endif //#ifndef _RGBDETECTOR_H_
