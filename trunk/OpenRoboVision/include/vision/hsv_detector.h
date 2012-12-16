//
// OpenRoboVision
//
// for detect objects by HSV-color
//
// ��� �������������� �� ����� � ������������ HSV
//
//
// robocraft.ru
//

#ifndef _HSV_DETECTOR_H_
#define _HSV_DETECTOR_H_

#ifdef USE_OPENCV

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

//
// ��������� ��� �������
//

// ���������� ����������� HSV-����
#define HSVDETECTOR_SHOW_HSV 0 
// ���������� ����������� ����� ���������� ��������������
#define HSVDETECTOR_SHOW_HSV_THRESHOLD 0
// ���������� ����������� ����� �������� ����
#define HSVDETECTOR_SHOW_HSV_AND 0
// �������� ����������� ����� ���������������� ��������������
#define HSVDETECTOR_SHOW_HSV_MORTH 1

class HSVDetector
{
	IplImage* img;
	IplImage* hsv;
	IplImage* h_plane;
	IplImage* s_plane;
	IplImage* v_plane;
	IplImage* and_img;
	IplImage* temp;
	IplImage* morth;
	IplConvKernel* Kern;

public:
	HSVDetector();
	~HSVDetector();

	// �������������
	void setup();
	void update();
	void make();

	// �������� ����� ���� ������� �� �����������
	bool getCenter(IplImage* image, CvPoint2D32f &center, float threshold=5);

	IplImage* result; // ��������� �� ����������� � ����������� ��������

	int Hmin;
	int Hmax;

	int Smin;
	int Smax;

	int Vmin;
	int Vmax;

	// ����, ����������� ������������ �� �������� S-����
	bool useSrange;
	// ����, ����������� ������������ �� ��������������� ��������������
	bool useMorthology;

private:
	// ��������� ������ ��� �����������
	void initImages(IplImage* image);
	// ������������ �����������
	void releaseImages();
	
};

#endif //#ifdef USE_OPENCV

#endif //#ifndef _HSV_DETECTOR_H_
