//
// OpenRoboVision
//
// base object for get frames from video devices
//
// ������� ������ ��� ��������� �����
//
//
// robocraft.ru
//

#ifndef _VIDEO_CAPTURE_H_
#define _VIDEO_CAPTURE_H_

#ifdef USE_OPENCV
# include <cv.h>
# include <highgui.h>
#endif //#ifdef USE_OPENCV

// �������� ���� ��� ������ �������� � ������
#define VIDEO_CAPTURE_WINDOW_NAME "capture"

class BaseVideoCapture
{
public:
	BaseVideoCapture();
	BaseVideoCapture(int width, int height);
	virtual ~BaseVideoCapture();

	// �������������
	virtual void init() = 0;
	// �������� ��������� ����
	virtual void update() = 0;
	// ���������� �����������
	virtual void end() = 0;

	// ������/������ �����
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	
	// ���������� ���� � ������
#ifdef USE_OPENCV
	IplImage* getFrame() {return frame;}
#else
	char* getFrame(int& size) { size = frame_size; return frame;}
#endif //#ifdef USE_OPENCV

	// ����� ���������� �� ����������� ��������
	void setShowCapture(bool show=false);

	//
	// ��� ���������� ���������
	//

#ifdef USE_OPENCV

	// ������������� ������ ��� ���������� ���������
	void initUndistortion(const char* intrinsics="intrinsics.xml", const char* distortion="distortion.xml");
	// ��������� �������� � ���������� ����������
	IplImage* getUndistort();

#endif //#ifdef USE_OPENCV

protected:
	void setup();

	int width;	// ������
	int height; // ������

#ifdef USE_OPENCV
	IplImage* frame;

	//
	// ��� ���������� ���������
	//

	// ������� � �������������� ���������
	// ������������� ������������
	CvMat* intrinsic;
	// ������������ ���������
	CvMat* distortion;
	// ������� ��� ���������� ���������
	IplImage* mapx;
	IplImage* mapy;
	// �������� � ���������� ����������
	IplImage* undist;

#else
	char* frame;
#endif //#ifdef USE_OPENCV
	int frame_size;

	// �������� ����
	const char* window_name;
	// ���� �������� ���������� �������� ��� ���
	bool show_capture;
};

#endif //#ifndef _VIDEO_CAPTURE_H_
