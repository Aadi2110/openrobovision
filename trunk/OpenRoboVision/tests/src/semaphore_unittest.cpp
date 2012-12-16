//
// OpenRoboVision
//
// test semaphore object
//
// ������������ ������� ��������
//
//
// robocraft.ru
//

#include "gtest/gtest.h"

#include "orv/system/thread.h"
#include "orv/system/semaphore.h"
#include "orv/system/times.h"

class S: public BaseThread
{
public:
	// �������� � ������������ ������ �� ���� � 
	// ������ �� �������.
	S(volatile int& flag, Semaphore& sem) :
	  _flag(flag), _sem(sem)
	  {}

	  void Execute() {
		  _sem.Wait();
		  _flag = 1;
	  }

private:
	volatile int& _flag;
	Semaphore& _sem;
};

TEST(Semaphore, Generic)
{
	// ��������� �������� ����� - 0.
	volatile int flag = 0;

	// ������� ������-�������
	Semaphore semaphore;
	
	// ������� ������������ ����� ����������.
	S a(flag, semaphore);
	// ��������� ���.
	a.Start();
	// ���� ��� �������� ������� �������, ����� ����
	// ����� ������������� ������ ��������� � ������
	// ����� �� ������ (1), �� ���� �� ������� ����������.
	orv::time::sleep(100);

	// �������� ����� ������ ���� ��� ��� 0, ��� ���
	// ������������ ����� ������ ���� ���������� ��
	// Wait()
	EXPECT_EQ(0, flag);

	// ������������� �������
	semaphore.Set();

	// ���� ���������� ������������� ������.
	a.Join();
	// ��� ��� ������������ ����� ����������, ��
	// ���� ������ ����� ������ ���� ����� 1.
	EXPECT_EQ(1, flag);
}
