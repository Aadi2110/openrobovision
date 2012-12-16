//
// ������ ���������� ������� ���������
//
// robocraft.ru
//

#ifndef _GIMBAL_H_
#define _GIMBAL_H_

#include <cv.h>
#include <stdio.h>

#include "orv/robo/arduino_firmata.h"
#include "orv/robo/pid.h"

class Gimbal
{
	// ��� ��� ����� ����
	Pid* pidAz;
	Pid* pidEl;

	// ��� ������ � ������������ Arduino/CraftDuino
	ArduinoFirmata* arduino;

public:
	Gimbal();
	Gimbal(int port, int rate);
	Gimbal(const char* port_name, int rate);
	~Gimbal();

	// �������������
	void setup();
	void update();
	void make(CvPoint current, CvPoint target);

	// ��������� ��������� ���� � �������� ���������
	void initServoPosition();

	// ������ �����, � ������� ���������� �����
	int pinAz;
	int pinEl;

	// ������� �������� ����
	int currentAz;
	int currentEl;

private:
	
};

#endif //#ifndef _GIMBAL_H_
