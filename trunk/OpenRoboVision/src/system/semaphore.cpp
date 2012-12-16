//
// OpenRoboVision
//
// Semaphore - object for threads synchronization
//
// Semaphore (�������) - ������ ��� ������������� �������
//
//
// robocraft.ru
//

#include "orv/system/semaphore.h"

//
// http://habrahabr.ru/blogs/programming/122108/
//

// ������������ ���������� ������� ������� Windows �� POSIX Threads:
// ���������� ��������� (conditional variable) + mutex. 
// �. �. ��������� ������ (��������������� �����), � conditional variable � ����, ������ � ���������. 
// ��������� ������ � ������ ������ ������ � ��������� �������� ��������� ����� ����� (����������������� ����� mutex), 
// � ������������ �����, ������� �������� �����, ���� ������� ���� ����������������. 

Semaphore::Semaphore()
{
#if defined(WIN32)
	_event = CreateEvent(0, FALSE, FALSE, 0); 
#elif defined(LINUX)
	pthread_mutex_init(&lock, 0);
	pthread_cond_init(&cond, 0);
	counter = 0;
#endif
}

Semaphore::~Semaphore()
{
#if defined(WIN32)
	CloseHandle(_event);
#elif defined(LINUX)
	pthread_cond_destroy( &cond );
	pthread_mutex_destroy( &lock );
#endif
}

// ����������
void Semaphore::Set()
{
#if defined(WIN32)
	SetEvent(_event); 
#elif defined(LINUX)
	pthread_mutex_lock( &lock );
	++counter;
	pthread_cond_signal( &cond );
	pthread_mutex_unlock( &lock );
#endif
}

// ����� ��������� �������� ����� �����������
bool Semaphore::Wait(DWORD millis)
{
#if defined(WIN32)
	DWORD res = WaitForSingleObject(_event, millis);
	return (res == WAIT_OBJECT_0 ? false : true);
#elif defined(LINUX)
	pthread_mutex_lock( &lock );
	int ret = 0;
	if(millis==INFINITE)
	{
		while (counter == 0)
		{
			// ���� �� ����������.
			// ���������� ������� �� ���������� ���������,
			// �����������, ��� �������� ����� ����������. 
			// ��� ����������� �������, ����� ��������������, 
			// � ���� ����� ��������� ���� � �����������
			ret = pthread_cond_wait(&cond, &lock);
		}
	}
	else
	{
		struct timespec tm;
		clock_gettime(CLOCK_REALTIME, &tm);
		tm.tv_sec += millis / 1000;					// �������
		tm.tv_nsec += (millis % 1000) * 1000000L;	// �����������
		// ���������� ������������
		// ( ���� tv_nsec ��������� 1000'000'000
		// �� ������� ���������� ������ EINVAL )
		if(tm.tv_nsec>1000000000L)
		{
			tm.tv_sec += 1;				
			tm.tv_nsec -= 1000000000L;
		}

		while (counter == 0)
		{
			ret = pthread_cond_timedwait(&cond, &lock, &tm);
			if( ret == ETIMEDOUT)
			{
				pthread_mutex_unlock( &lock );
				return true;
			}
		}
	}
	// �����, ���� ������ ���� ���������� - ����� ��� ��������
	// � �������������� �������.
	--counter;
	pthread_mutex_unlock( &lock );
	return false;
#endif
}
