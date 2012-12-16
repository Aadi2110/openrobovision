//
// OpenRoboVision
//
// set of objects and methods for Robots Vision
// based on OpenCV
//
// ����� �������� � ������� ��� ������ �������
// ���������� �� OpenCV
//
//
// Author: 	Vladimir  aka noonv
// email: 	noonv13@gmail.com
// site:	robocraft.ru
//

OpenRoboVision - ��� ����� �++ ������� � ������� ������ ���������� ������������� ������ - OpenCV.

��������� ORV:
* ������
* ������
* ������

������ ORV ���������� ������ � ������, ������� ������� ��� ����� �� ����� ���� ������������ ���������� �� ������, �.�. ������ �������� � ������������ � ����� ��������.

��������, ����� �������� � OpenCV � ������� ����� ��������:

//
// ������ ������ � ������� �� OpenCV
//

#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	// �������� ����� ������������ ������
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);
	assert( capture );

	//cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
	//cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);

	// ������ ������ � ������ �����
	double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	double height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	printf("[i] %.0f x %.0f\n", width, height );

	IplImage* frame=0;

	cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	int counter=0;
	char filename[512];

	while(true){
		// �������� ����
		frame = cvQueryFrame( capture );

		// ����������
		cvShowImage("capture", frame);
	
		char c = cvWaitKey(33);
		if (c == 27) { // ������ ESC
			break;
		}
		else if(c == 13) { // Enter
			// ��������� ���� � ����
			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			cvSaveImage(filename, frame);
			counter++;
		}
	}
	// ����������� �������
	cvReleaseCapture( &capture );
	cvDestroyWindow("capture");
	return 0;
}

� ��� ��� ����� ��������� ��� �� ��������� � �������������� ORV:

//
// ������ ������ � ������� c OpenRoboVision
//

#include "orv.h"
#include "vision/camera.h"

int main(int argc, char* argv[])
{
	Camera camera(CV_CAP_ANY);

	IplImage* frame=0;

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	int counter=0;
	char filename[512];

	while(true){
		// �������� ����
		camera.update();
		frame = camera.getFrame();
	
		char c = cvWaitKey(33);
		if (c == 27) { // ������ ESC
			break;
		}
		else if(c == 13) { // Enter
			// ��������� ���� � ����
			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			cvSaveImage(filename, frame);
			counter++;
		}
	}
	return 0;
}

������ Camera �������� � ���� ��� �� ��������, ������� ����� ���� �������� ����� �������. ��� ��, ������ ��� ��������� �� ����� ������������ �������.


�.�. OpenRoboVision �� ��������� ����� OpenCV, � ���������. ����� ��� ������������� ����� �������.

����������, � OpenCV, ������� � ������ 2.0 ��� ���� ���������� �++ -������, ��������:
VideoCapture
VideoWriter 
� ����� ������������ ��, �� ������ Camera ��� �� �������� ������� ��� ���������� ��������� � ����� ���� ������� ������� �������� ��������������� ���������.


������ ������, ������������ ORV (�� �������� ���������� �� � �������) - ��� Web-cam-bot. ���������� �����, ��������� �� ���� ����, ����������� Arduino/CraftDuino � ������� web-������, ������������ � ��.

Web-cam-bot ��������� �������������� ����� ����������� ��������� �������� ������.

�� ������ ORV, ������ ������� �� ��������� Bot � Gimbal.
Bot - ��� ���������� ������ ����, ������� �������� � ���� �������: 
Camera* camera; // ������
Gimbal* gimbal; // ���������� �������
HSVDetector* detector; // �������� ������� (�� �����)


������ Gimbal ��������� �������, �������������� � Arduino, �� ��������� Firmata. 
��� �������� ������������ �������� ������������ ��� (������ Pid).

������ HSVDetector ��������� �� �������� ���������� HSV �������� �� ����������� �� ��� �����.

�.�. �������� ������ Web-cam-bot-� �������� �����:
* �������� �������� � ������ ( cvCopy(camera->getFrame(), image); )
* ����� ����� ����� �� �������� ������ ( bool result=detector->getCenter( image, point, BOT_THRESHOLD); )
* ���� ������ ���������, �� ��������� ������ �.�. ����� ����� ���� � ������ �������� ( gimbal->make( cvPoint(image->width/2, image->height/2), cvPointFrom32f(point) ); )


�.�. ����� ORV-������� ��������� ������ ������������� ������ ������������� ������ �������.


���������:
����������� OpenRoboVision � ������� ����������.
��������� � Visual Studio ��� ���������� ������� ���� �� ���������� � orv.h � ���������� � ����������� OpenRoboVision.lib
�������� �������� ������� 
#include "orv.h"
����� �������� ������������ :)
�������� ��������, ��� ���������� OpenCV ������ ���� �����������, � Visual Studio ��� ��������� �� ������ � ���.
�� ������ ������ ��������������(��������� � ������) ������ OpenCV 2.0 � ������


������ ������������� OpenRoboVision ����� ���������� � ������� WebCamBot.
������� WebCamBot � OpenRoboVision ��������� � ����� ����������, ������� � ���������� ������� WebCamBot ��������� ������������� ����:

AdditionalIncludeDirectories="../OpenRoboVision/include;"
AdditionalDependencies="./Release/orv.lib"


-= TODO =-

- �������� ������ ��������� ����������� ��� OpenCV
- ��������� ���������� orv_image � Image
- �������� ����������� �� ������� ������ ���, ��� ��� ����������,
  � ��������� - �������� �� �� ����������
- ������������ _������_ ��������� ������ ��� ������ � ��������

-= HISTORY =-

2012-06-26 - v.0.2.12
	+ � Stream � Socket ��������� ������ available() � waitInput()
	+ � Serial ���������: ��������� ����� ��� ������, ��������, ����-���,
		��� Linux �������� ����� setLowLatency() // ����� �������� ����� ��������� �����
2012-05-18 - v.0.2.11
	+ �������� ����� ��� ������ � �������� (system/network.h)
	+ �������� ����� ������������ MJPG, ��������� �������� ������ 
		�� mjpg-streamer (video/camera_mjpg.h)
2012-05-02 - v.0.2.10
	! ������������ ����� ���������� � include/orv/
2012-04-06 - v.0.2.9
    ! ������ ���������� ��������� ORCP ��� Arduino (docs/orcp)
	! robo/orv_cp.h -> robo/orcp.h
	! docs/pp-protocol.txt -> docs/orcp.txt
	! � ORCP ������ �������� �������� ����������� �����
	(������ CRC16 - ������ ������� XOR)
2012-04-05 - v.0.2.8 
	! ������ ���������� ORCP - ORV Communication Protocol (robo/orv_cp.h)
2012-04-04 - v.0.2.8 
	+ ��������� ������ ��� �������� CRC (system/crypto.h)
	+ ��������� ������ �����������/������������� SLIP (system/slip.h)
	+ �������������� ������
2012-04-03 - v.0.2.7 
	+ �������� ConfigParser (system/config_parser.h) - ������� ������ 
		���������������� ������ ���� (key=value)
	+ ��������� ������ ��� ������ ����� (system/log.h)
	+ �������������� ������
2012-03-28 - v.0.2.6 
	+ �������� ����������� ����� Stream, �� �������� ������ ����������� Serial
	! ������� ������ Serial: Open, Close, Write, Read 
	 (��������� ������ open close write read)
	- ������� ���� Serial.port_number
	+ �������� ����� Serial.getLSR() (����������� ������ ��� Linux!)
	+ �������������� ������
2012-01-01 - v.0.2.5 
	+ ���������� robo/roomba system/types system/times
2011-12-29 - v.0.2.4 
	������ �������� orv_image � Image
2011-12-15 - v.0.2.3 
	+ �������� orv::Image (vision/image.h)
2011-12-15 - v.0.2.2 
	+ �������� Framereader (vision/frame_reader.h)
2011-11-17 - v.0.2.1 
	+ �������� CameraV4L2 (vision/camera_v4l2.h)
2011-10-25 - v.0.2.0 
	! ������ ��� �_� �������� ��������� ������ �������� �����
2010-10-17 - v.0.1.0 
	! ������ ������ ��������������� ��� OpenRoboVision

