//
// OpenRoboVision
//
// ������ ������ �����
//

#include "orv.h"
#include "vision/videoreader.h"

int main(int argc, char* argv[])
{
	// ������� ������ ������ �����
	Videoreader reader("capture.avi");

	IplImage* frame=0;

	printf("[i] press Esc for quit!\n\n");

	int counter=0;
	char filename[512];

	while(true){

		// ��������� ����
		reader.update();
		// ��������� ����
		frame = reader.getFrame();

		if(frame){
			// ��������� ���� � ����
			sprintf(filename, "frame%05d.jpg", counter);
			printf("[i] write frame: %s\n", filename);
			cvSaveImage(filename, frame);
			counter++;
		}
		else{
			break;
		}
	
		char c = cvWaitKey(33);
		if (c == 27) { // ������ ESC
			break;
		}
	}
	return 0;
}
