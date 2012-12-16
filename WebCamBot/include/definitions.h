//
// �����������
//

#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include "orv/orv.h"

// ������������ ������ ����� ��-���������
#define CAMERA_USE_DEFAULT_SIZE 1
// ������ �������� �� ������
#define CAMERA_WIDTH 640 
#define CAMERA_HEIGHT 480

// COM-���� � �������� ��������� ����������
#if defined(WIN32)
# define GIMBAL_PORT "COM5"
#elif defined(LINUX)
# define GIMBAL_PORT "/dev/ttyS0"
#endif
// �������� ������
#define GIMBAL_RATE 9600

// ������ ����� ����������� Arduino/CraftDuino � ������� ���������� �����
#define GYMBAL_SERVO_PIN_AZ 8
#define GYMBAL_SERVO_PIN_EL 7

// ��������� ���� ��������� ����
#define GYMBAL_SERVO_INIT_AZ 30
#define GYMBAL_SERVO_INIT_EL 40

//
// ��������� ��� ����������� ������� �� ����� (� ��������c��� HSV)
//
#if 1
#define H_min 13
#define H_max 85
#define S_min 0
#define S_max 100
#define V_min 220
#define V_max 256
#else
#define H_min 0
#define H_max 256
#define S_min 0
#define S_max 256
#define V_min 0
#define V_max 256
#endif

// ����������� ����� �������� �������
#define BOT_THRESHOLD 5

// ������������ PID
#define K_P 0.05f
#define K_I 0.001f
#define K_D -0.001f
#define PID_MAXERROR 1

#endif //#ifndef _DEFINITIONS_H_
