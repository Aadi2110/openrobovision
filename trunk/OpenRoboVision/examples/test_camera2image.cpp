//
// OpenRoboVision
//
// ������ ������ � �������
//

#include "orv/orv.h"
#include "orv/vision/camera.h"
#include "orv/vision/image.h"

int main(int argc, char* argv[])
{
	Camera camera(CV_CAP_ANY);
	camera.setShowCapture(false);

	printf("[i] press Enter for capture image and Esc for quit!\n\n");

	int counter=0;
	char filename[512];

	orv::Image image;

	while(true){

		// �������� ����
		camera.update();

		if( camera.getFrame() ){
			orv::Image frame( camera.getFrame() );
			image = frame;
			image.show("capture image");
		}
	
		char c = cv::waitKey(33);
		if (c == 27) { // ������ ESC
			break;
		}
		else if(c == 13) { // Enter
			// ��������� ���� � ����
			sprintf(filename, "Image%d.jpg", counter);
			printf("[i] capture... %s\n", filename);
			image.save(filename);
			counter++;
		}
	}
	return 0;
}
