//
// OpenRoboVision
//
// object for get frames from camera via videoInput library
//
// ������ ��� ��������� �������� � �����������
// ����� ���������� videoInput
//
//
// robocraft.ru
//

#if defined(USE_OPENCV) && defined(WIN32) && defined(USE_VIDEOINPUT_LIB)

#include "orv/vision/camera_vi.h"

CameraVI::CameraVI():
	rate(0),
	device(0)
{
	init();
}

CameraVI::CameraVI(int _width, int _height, int _rate, int _device):
rate(0),
device(0)
{
	width = _width;
	height = _height;
	rate = _rate;
	device = _device;

	init();
}

CameraVI::~CameraVI() 
{
	this->end();
}

// �������������
void CameraVI::init()
{
	int numDevices = VI.listDevices();
	if(rate)
	{
		VI.setIdealFramerate(device, rate); // ��������� ������� ������
	}
	
	VI.setupDevice(device, width, height);

	frame = cvCreateImage(cvSize(VI.getWidth(0),VI.getHeight(0)), IPL_DEPTH_8U, 3);
}

// ��������� ���������� �����
void CameraVI::update()
{
	if (VI.isFrameNew(device))
	{
		VI.getPixels(device, (unsigned char *)frame->imageData, false, true); 

		if(show_capture)
		{
			cvShowImage(window_name, frame);
		}
	}
}

// ���������� �����������
void CameraVI::end()
{
	remove_frame();
	VI.stopDevice(device);
}

// �������� ������ � ����������� ������
void CameraVI::showCameraSettings()
{
	VI.showSettingsWindow(device);
}

int CameraVI::getWidth()
{
	return VI.getWidth(device);
}

int CameraVI::getHeight()
{
	return VI.getHeight(device);
}

#endif //#if defined(USE_OPENCV) && defined(WIN32) && defined(USE_VIDEOINPUT_LIB)
