//
// OpenRoboVision
//
// optical flow (piramid Lucas-Kanade)
//
//
// robocraft.ru
//

#include "orv/vision/optical_flow.h"

#ifdef USE_OPENCV

OpticalFlowLK::OpticalFlowLK()
{
	init();
}

OpticalFlowLK::~OpticalFlowLK() 
{
	if(imgA)
		cvReleaseImage(&imgA);
	if(imgB)
		cvReleaseImage(&imgB);
	if(eig_image)
		cvReleaseImage(&eig_image);
	if(tmp_image)
		cvReleaseImage(&tmp_image);
	if(pyrA)
		cvReleaseImage(&pyrA);
	if(pyrB)
		cvReleaseImage(&pyrB);
	if(cornersA!=0){
		delete []cornersA;
		cornersA=0;
	}
	if(cornersB!=0){
		delete []cornersB;
		cornersB=0;
	}
	if(featuresFound!=0){
		delete []featuresFound;
		featuresFound=0;
	}
	if(featureErrors!=0){
		delete []featureErrors;
		featureErrors=0;
	}
}

// �������������
void OpticalFlowLK::init()
{
	imgA=0;
	imgB=0;
	eig_image=0;
	tmp_image=0;
	pyrA=0;
	pyrB=0;

	cornerCount = 0;

	cornersA= new CvPoint2D32f[ LK_MAX_CORNERS ];
	cornersB= new CvPoint2D32f[ LK_MAX_CORNERS ];

	featuresFound = new char[ LK_MAX_CORNERS ];
	featureErrors = new float[ LK_MAX_CORNERS ];

	if(!cornersA || !cornersB || !featuresFound || !featureErrors)
	{
		fprintf(stderr, "[!][OpticalFlowLK] Error: cant allocate memory!\n");
		return;
	}
}

// ��������� ����������� ��� ���������
void OpticalFlowLK::setA(IplImage* src)
{
	if(!src)
		return;
	if(imgA!=0)
	{
		cvReleaseImage(&imgA);
		imgA=0;
	}
	if(eig_image!=0)
	{
		cvReleaseImage(&eig_image);
		cvReleaseImage(&tmp_image);
		eig_image=0;
		tmp_image=0;
	}
	imgA = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	eig_image = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);
	tmp_image = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);

	if(!imgA || !eig_image || !tmp_image)
	{
		fprintf(stderr, "[!][OpticalFlowLK] Error: cant allocate memory!\n");
		return;
	}

	cvConvertImage(src, imgA, CV_BGR2GRAY);
}

void OpticalFlowLK::setB(IplImage* src)
{
	if(!src)
		return;
	if(imgB!=0){
		cvReleaseImage(&imgB);
		imgB=0;
	}
	imgB = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

	cvConvertImage(src, imgB, CV_BGR2GRAY);
}

void OpticalFlowLK::releaseAB()
{
	if(imgA)
		cvReleaseImage(&imgA);
	if(eig_image)
		cvReleaseImage(&eig_image);
	if(tmp_image)
		cvReleaseImage(&tmp_image);
	if(imgB)
		cvReleaseImage(&imgB);
	imgA=0;
	eig_image=0;
	tmp_image=0;
	imgB=0;
}

// ����� ����������� ������
void OpticalFlowLK::make()
{
	if(!imgA || !imgB || !eig_image || !tmp_image)
	{
		return;
	}

	int i=0;

#if 1
	cornerCount = LK_MAX_CORNERS;
	//
	// ������� ����� ��� ������������ �����������
	//
	cvGoodFeaturesToTrack( imgA, eig_image, tmp_image, 
							cornersA,		// ������������ �������� �������� �����
							&cornerCount,	// ������������ �������� ����� �������� �����
							0.01,			// ���������, ������������ ���������� ���������� �������� �����
							5.0,			// ������, ������������ ����������-��������� ��������� ����� ������
							0,				// �����, ������������ ROI (���� NULL, �� ����� �� ����� �����������)
							5,				// ������ �������� �����
							0,				// ���� !=0 ������������ cvCornerHarris(), ����� cvCornerMinEigenVal()
							0.04 );			// �������� ��� cvCornerHarris()
#else
	//
	// ������� ����������� ����������� ������ �� �����
	//
	int step_x = imgA->width / 5;
	int step_y = imgA->height / 5;

	int points_count = (imgA->width / step_x + 1) * (imgA->height / step_y + 1);

	if(points_count>LK_MAX_CORNERS){
		delete []cornersA;
		cornersA=0;
		delete []cornersB;
		cornersB=0;

		cornersA= new CvPoint2D32f[ points_count ];
		cornersB= new CvPoint2D32f[ points_count ];
		featuresFound = new char[ points_count ];
		featureErrors = new float[ points_count ];
		assert(cornersA);
		assert(cornersB);
		assert(featuresFound);
		assert(featureErrors);
	}

	cornerCount = 0;
	for ( j = 1; j < imgA->height; j += step_y){
		for ( i = 1; i < imgA->width; i += step_x){
			cornersA[cornerCount] = cvPoint2D32f((float)i, (float)j);
			cornerCount++;
		}
	}
#endif

	//
	// ��������� ��������� ����� � ������������� ���������
	//
	cvFindCornerSubPix( imgA, cornersA, cornerCount,
						cvSize(LK_WINDOW_SIZE, LK_WINDOW_SIZE), // ������ �������� ����� ���� ��� ������
						cvSize(-1,-1),
						cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, LK_ITER_COUNT, 0.03) );

	// ���������� ������ �������� 
	CvSize pyr_sz = cvSize( imgA->width+8, imgB->height/3 );

	if(pyrA!=0)
	{
		cvReleaseImage(&pyrA);
		cvReleaseImage(&pyrB);
	}
	pyrA = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
	pyrB = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );

	//
	// ������� ���������� �����
	//
	cvCalcOpticalFlowPyrLK( imgA, imgB, pyrA, pyrB,
							cornersA,
							cornersB,
							cornerCount,
							cvSize( LK_WINDOW_SIZE, LK_WINDOW_SIZE ),// ������ ���� ������ ������� ������ ��������
							5,										 // ������������ ������� ��������.
							featuresFound, // ���� ������� ������� ���������� � 1, �� �������������� ������ ����� ���� ����������
							featureErrors, // ������ �������� ����� ������������� � ���������� ������� (����� ���� NULL)
							cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, LK_ITER_COUNT, .3 ),
							0 );

	center.x=0.0;
	center.y=0.0;
	cornerCountGood = 0;
	for( i=0; i<cornerCount; i++ )
	{
		// ���������� ����������� ����� � ����� � ������� �������
		if( featuresFound[i]==0 || featureErrors[i]>LK_MAX_FEATURE_ERROR ) {
			center.x += cornersB[i].x;
			center.y += cornersB[i].y;
			cornerCountGood++;
		}
	}

	if(cornerCountGood)
	{
		center.x /= cornerCountGood;
		center.y /= cornerCountGood;
	}

}

// �������� ���������
void OpticalFlowLK::show()
{
	if(!imgA || !imgB)
	{
		return;
	}

	//
	// �������� ����� ����� ���������� ������� 
	//
	IplImage* imgC = cvCreateImage(cvGetSize(imgB), IPL_DEPTH_8U, 3);
	cvConvertImage(imgB, imgC, CV_GRAY2BGR);

	for( int i=0; i<cornerCount; i++ )
	{
		// ���������� ����������� ����� � ����� � ������� �������
		if( featuresFound[i]==0 || featureErrors[i]>LK_MAX_FEATURE_ERROR )
		{
			//printf("Error is %f/n",feature_errors[i]);
			continue;
		}
		//    printf("Got it/n");
		CvPoint p0 = cvPoint(
			cvRound( cornersA[i].x ),
			cvRound( cornersA[i].y )
			);
		CvPoint p1 = cvPoint(
			cvRound( cornersB[i].x ),
			cvRound( cornersB[i].y )
			);
		cvLine( imgC, p0, p1, CV_RGB(255,0,0), 1);
	}

	// �����
	cvCircle(imgC, cvPointFrom32f(center), 5, CV_RGB(255, 98, 0), -1);

	// ����������
	cvNamedWindow("ImageA");
	cvNamedWindow("ImageB");
	cvNamedWindow("LKpyr_OpticalFlow");
	cvShowImage("ImageA", imgA);
	cvShowImage("ImageB", imgB);
	cvShowImage("LKpyr_OpticalFlow", imgC);

	cvReleaseImage(&imgC);
}

#endif //#ifdef USE_OPENCV
