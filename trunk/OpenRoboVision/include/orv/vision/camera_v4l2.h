//
// OpenRoboVision
//
// object for get frames from camera under Linux (via V4L2)
//
// ������ ��� ��������� �������� � ����������� ��� Linux-�� (����� V4L2)
//
//
// robocraft.ru
//

#ifndef _CAMERA_V4L2_H_
#define _CAMERA_V4L2_H_

# if defined(LINUX) && defined(USE_V4L2_LIB)

#include "video_capture.h"

//
// default params
//

// image size
#define DEFAULT_V4L2_IMAGE_WIDTH 320
#define DEFAULT_V4L2_IMAGE_HEIDHT 288
#define DEFAULT_V4L2_FPS 25 // PAL/SECAM

// video device
#define DEFAULT_V4L2_DEV_NAME "/dev/video0"

// save image?
#define VIDEOV4L2_SAVE_IMAGE 0

// V4L2 structure
struct buffer {
	void *                  start;
	size_t                  length;
};

#define CLEAR(x) memset(&(x), 0, sizeof((x)))

class CameraV4L2 : public BaseVideoCapture
{
public:

	// ����� ��������� ������ � ����������
	enum io_method {IO_METHOD_READ, IO_METHOD_MMAP, IO_METHOD_USERPTR};

	CameraV4L2(const char* dev_name=DEFAULT_V4L2_DEV_NAME);
	CameraV4L2(const char* dev_name, int width, int height, int fps=DEFAULT_V4L2_FPS, io_method method=IO_METHOD_MMAP);
	~CameraV4L2();

	// �������������
	void init();
	// �������� ��������� ����
	void update();
	// ���������� �����������
	void end();

	// ������/������ �����
	int getWidth() {return width; }
	int getHeight() {return height; }

	const char* getDevName() const { return dev_name.c_str(); }
	int getFd() const { return fd; }
	int getFPS() const { return fps; }
	unsigned long getImageCounter() const { return imageCounter; }

private:

#if defined(USE_OPENCV)
	// �������� �������� �� ������� ������
	IplImage* makePictureFromData(const char* src, int src_size);
#endif //#if defined(USE_OPENCV)

	//
	// ������ V4L2
	//

	// ������� ���� ����������
	void open_device(const char* dev_name);
	// �������������
	void init_device();
	// ������ �������
	void start_capturing();
	// ��������� �������
	void stop_capturing();
	// ���������������
	void uninit_device();
	// ������� ���� ����������
	void close_device();
	// ������ ������������� ����������� ��� 
	// ��������� ���� ��������� ������
	void init_userp(unsigned int buffer_size);
	void init_mmap();
	void init_read(unsigned int buffer_size);
	// "����" ��������� �����
	void mainloop();
	// ���������� �����
	int read_frame();
	// ��������� ������ �����
	void process_image(const void* p);

	bool initialised; // ���� �������������

	// ���������� ��� ������������
	std::string dev_name;
	// ���������� ��������� ����������
	int fd;
	// ����� ��������� ������
	io_method		io;
	// ������ ��� ����� ������
	struct buffer* buffers;
	unsigned int n_buffers;
	// FPS
	int fps;
	// ������ ������ ��� ����
	int buf_size;

	// ������� ������
	unsigned long imageCounter;

	//
	// libv4l2cam
	//
	int mb, Mb, db, mc, Mc, dc, ms, Ms, ds, mh, Mh, dh, msh, Msh, dsh;
	bool ha;

public:
	int minBrightness() const { return mb; }
	int maxBrightness() const { return Mb; }
	int defaultBrightness() const { return db; }
	int minContrast() const { return mc; }
	int maxContrast() const { return Mc; }
	int defaultContrast() const { return dc; }
	int minSaturation() const { return ms; }
	int maxSaturation() const { return Ms; }
	int defaultSaturation() const { return ds; }
	int minHue() const { return mh; }
	int maxHue() const { return Mh; }
	int defaultHue() const { return dh; }
	bool isHueAuto() const {return ha; }
	int minSharpness() const { return msh; }
	int maxSharpness() const { return Msh; }
	int defaultSharpness() const { return dsh; }

	int setBrightness(int v);
	int setContrast(int v);
	int setSaturation(int v);
	int setHue(int v);
	int setHueAuto(bool v);
	int setSharpness(int v);

#if defined(USE_OPENCV)
	// �������� �������� �� ������� ������ YUYV
	void YUYVdata_to_IplImage(const char* src, int src_size, IplImage *dst);
#endif //#if defined(USE_OPENCV)

};

#endif //# if defined(LINUX) && defined(USE_V4L2_LIB)

#endif //#ifndef _CAMERA_V4L2_H_
