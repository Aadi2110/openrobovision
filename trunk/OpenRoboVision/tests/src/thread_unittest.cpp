//
// OpenRoboVision
//
// test threads object
//
// ������������ ������� �������
//
//
// robocraft.ru
//

//
// http://easy-coding.blogspot.com/2009/01/threadcpp.html
//

#include "gtest/gtest.h"

#include "orv/system/thread.h"
#include "orv/system/times.h"

class SimpleThread : public BaseThread
{
public:
	SimpleThread():__done(false) { }

	bool done() const { return __done; }

protected:
	void Execute() {
		__done = true;
	}

private:
	bool __done;
};

// ����������� ���� � ������ RunningInParallel � ������ ������ ThreadTest.
TEST(Thread, Generic)
{
	// ������� ������ ������ ������
	SimpleThread thread;
	// ��������! ������ EXPECT_FALSE �������, ����� �������� � ��� ���������.
	// ���� ��� ����, �� ��� ���������, � ���������� ����� ���� ������. ���� �� ���,
	// �� ���������� ��������� �� ������, ���� ���� ���������� ������.
	// � ����� ������ ��� ������ ���� false �� ������.
	EXPECT_FALSE(thread.done());
	// ��������� ����� �� ����������
	thread.Start();
	// ���� ���������� ������
	thread.Join();
	// ������ EXPECT_TRUE �������, ����� �������� � ��� ���������.
	// ���� ��� ������, �� ��� ���������, � ���������� ����� ���� ������. ���� �� ���,
	// �� ���������� ��������� �� ������, ���� ���� ���������� ������.
	// ��� �� ��� ���� �� false, � true, ������ ��� ����� ������ ��� �������� ��������
	// ����� �����.
	EXPECT_TRUE(thread.done());
}


// "������������ �����"
class EternalThread: public BaseThread
{
protected:

	void Execute() {
		// ������ ����� ����� �������� �����, ���� ��� �� ����� �����.
		while (true) {
			orv::time::sleep(1);
		}
	}
};

TEST(Thread, Kill)
{
	// ������� "������" �����
	EternalThread thread;
	// ��������� ���
	thread.Start();
	// ������� ���
	thread.Kill();
	// ���� ������� Kill() �� ��������, �� �� ������� �� �������� ��������� ������
	// � ��������� ��� ��������.
	thread.Join();
}
