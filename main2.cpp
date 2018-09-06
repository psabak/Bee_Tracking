/*
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap("D:/OneDrive/Počítač/Škola/OpenCV_Learning/VideoSamples/vcely0.mp4"); //capture the video from webcam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

												//black lines bees
	int bLowH = 0;
	int bHighH = 25;

	int bLowS = 0;
	int bHighS = 200;

	int bLowV = 0;
	int bHighV = 255;

	//yellow lines bees
	int iLowH = 11;
	int iHighH = 33;

	int iLowS = 44;
	int iHighS = 107;

	int iLowV = 47;
	int iHighV = 225;


	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	int iLastX = -1;
	int iLastY = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;


	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		//Mat imgHSV;

		//GaussianBlur(imgHSV, imgHSV, Size(3,3), 0, 0 );


		//inRange(imgHSV, Scalar(bLowH, bLowS, bLowV), Scalar(bHighH, bHighS, bHighV), imgHSV); //Threshold the image
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgHSV); //Threshold the image

																									  //morphological opening (removes small objects from the foreground)
		erode(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
		dilate(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
		erode(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgHSV);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if (dArea > 10000)
		{
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;

			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0, 0, 255), 2);
			}

			iLastX = posX;
			iLastY = posY;
		}

		imshow("Thresholded Image", imgHSV); //show the thresholded image
													 //imshow("Original Image", imgOriginal); //show the original image

		imgOriginal = imgOriginal + imgLines;

		imshow("Original Image", imgOriginal);

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}*/