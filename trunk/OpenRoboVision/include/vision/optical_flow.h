//
// OpenRoboVision
//
// optical flow (piramid Lucas-Kanade)
//
// ���������� ����� (������������� �����-������)
//
//
// robocraft.ru
//

#ifndef _OPTICAL_FLOW_H_
#define _OPTICAL_FLOW_H_

#ifdef USE_OPENCV

# include <cv.h>
# include <highgui.h>

#define LK_MAX_CORNERS 100
#define LK_WINDOW_SIZE 10

// ������������ ����� ��������
#define LK_ITER_COUNT 20
#define LK_MAX_FEATURE_ERROR 500 //550

class OpticalFlowLK
{
	// ������ �����������
	IplImage* imgA;
	// ������ �����������
	IplImage* imgB;
	// ��������� ����������� ��� ���������� ����� ��� ������������
	IplImage* eig_image;
	IplImage* tmp_image;
	// ��� �������� ������� �����������
	IplImage* pyrA;
	// ��� �������� ������� �����������
	IplImage* pyrB;

public:
	OpticalFlowLK();
	~OpticalFlowLK();

	// �������������
	void init();

	// ��������� ����������� ��� ���������
	void setA(IplImage* src);
	void setB(IplImage* src);
	IplImage* getA(){return imgA;}
	IplImage* getB(){return imgB;}
	void releaseAB();

	// ����� ����������� ������
	void make();

	// �������� ���������
	void show();

	// ��� �������� ��������� �����
	CvPoint2D32f* cornersA;
	CvPoint2D32f* cornersB;

	// ������ ����� - ������� ��� ���
	char* featuresFound;
	// ������ ������
	float* featureErrors;

	// ���������� ��������� �����
	int cornerCount;

	// ����� ���� ������ ���������
	CvPoint2D32f center;
	// ���������� �����, �������������� ��� �������� ������ ����
	int cornerCountGood;

private:

};

#endif //#ifdef USE_OPENCV

#endif //#ifndef _OPTICAL_FLOW_H_
