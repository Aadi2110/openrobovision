//
// OpenRoboVision
//
// object for get frames from camera (via OpenCV)
//
// ������ ��� ��������� �������� � ����������� (����� OpenCV)
//
//
// robocraft.ru
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#ifdef USE_OPENCV

#include "video_capture.h"

class Camera : public BaseVideoCapture
{
public:
	Camera();
	Camera(int camera_index);
	Camera(int width, int height);
	Camera(int camera_index, int width, int height);
	~Camera();

	// �������������
	void init();
	// �������� ��������� ����
	void update();
	// ���������� �����������
	void end();

	// ������/������ �����
	int getWidth();
	int getHeight();

	// �������� �������� 
	double getParam(int paramId);
	// ���������� ��������
	int setParam(int paramId, double value);

private:
	CvCapture* capture;

	int device; // ����� ������ � �������
	int rate;	// ������� ������
};

#endif //#ifdef USE_OPENCV

#endif //#ifndef _CAMERA_H_
