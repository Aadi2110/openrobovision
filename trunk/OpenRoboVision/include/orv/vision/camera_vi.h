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

#ifndef _CAMERAVI_H_
#define _CAMERAVI_H_

#if defined(USE_OPENCV) && defined(WIN32) && defined(USE_VIDEOINPUT_LIB)

#include "video_capture.h"

#include <videoInput.h>

//
// ��� �������� ��������  ���� ����������: videoInput.lib 
// � ��������� ������ ���������� �������� �������: /NODEFAULTLIB:"atlthunk"
// 
// �������� ��� �������� ���� ����������: videoInput.lib 
#ifdef _MSC_VER
# pragma message ("Using library: videoInput.lib")
# pragma comment(lib, "videoInput.lib")
# pragma message ("Add to linker string:  /NODEFAULTLIB:\"atlthunk\"")
#endif

class CameraVI : public BaseVideoCapture
{
public:
	CameraVI();
	CameraVI(int width, int height, int rate=0, int device=0);
	~CameraVI();

	// �������������
	void init();
	// ��������� ���������� �����
	void update();
	// ���������� �����������
	void end();

	// ������/������ �����
	int getWidth();
	int getHeight();

	// �������� ������ � ����������� ������
	void showCameraSettings();

private:

	videoInput VI;

	int device; // ����� ������ � �������
	int rate;	// ������� ������
};

#endif //#if defined(USE_OPENCV) && defined(WIN32) && defined(USE_VIDEOINPUT_LIB)

#endif // #ifndef _CAMERAVI_H_
