
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#ifdef WINDOWS
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows
#endif

#include "Blob.h"

// global variables ///////////////////////////////////////////////////////////////////////////////
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);


//int bLowH = 0;
//int bHighH = 25;

//int bLowS = 0;
//int bHighS = 200;

//int bLowV = 0;
//int bHighV = 255;

//yellow lines bees
//int iLowH = 11;
//int iHighH = 33;

//int iLowS = 44;
//int iHighS = 107;

//int iLowV = 47;
//int iHighV = 225;

/////////////////////////////////////////////////////////////////////////////////////////////////// 

const int WIDTH = 640;
const int HEIGHT = 360;

const int CAPACITY = 40;
int direction[CAPACITY][2];
int POSITION = 0;
std::array<int, 2> a[CAPACITY];
bool alreadyExecuted = false;

int main(void) {
    
	cv::VideoCapture capVideo;
	cv::Mat imgFrame1;
	cv::Mat imgFrame2;

	capVideo.open("D:/DP/13.mp4");

	if (!capVideo.isOpened()) {
		std::cout << "\nerror reading video file" << std::endl << std::endl;
	#ifdef WINDOWS
		_getch();
	#endif
		return(0);
	}

	if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
		std::cout << "\nError: video file must have at least two frames";
	#ifdef WINDOWS
		_getch();
	#endif
		//return(0);
	}

	capVideo.read(imgFrame1);
	capVideo.read(imgFrame2);
        resize(imgFrame1, imgFrame1, cv::Size(WIDTH, HEIGHT), 0, 0, cv::INTER_CUBIC);
        resize(imgFrame2, imgFrame2, cv::Size(WIDTH, HEIGHT), 0, 0, cv::INTER_CUBIC);
        
        //Create a black image with the size as the camera output
	cv::Mat imgLines = cv::Mat::zeros(imgFrame1.size(), CV_8UC3);;
        resize(imgLines, imgLines, cv::Size(WIDTH, HEIGHT), 0, 0, cv::INTER_CUBIC);

	char chCheckForEscKey = 0;

	while (capVideo.isOpened() && chCheckForEscKey != 27) {

		std::vector<Blob> blobs;

		capVideo.read(imgFrame2);
                resize(imgFrame2, imgFrame2, cv::Size(WIDTH, HEIGHT), 0, 0, cv::INTER_CUBIC);
		
		/*
		
		cv::Mat imgHSV;

		cvtColor(imgFrame2, imgHSV, cv::COLOR_BGR2HSV);

		// transform to thresholded image


		inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgHSV);

		erode(imgHSV, imgHSV, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));
		dilate(imgHSV, imgHSV, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgHSV, imgHSV, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));
		erode(imgHSV, imgHSV, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2, 2)));

		imgHSV.setTo(cv::Scalar(0, 0, 0), imgHSV);

		cvtColor(imgHSV, imgFrame2, cv::COLOR_HSV2BGR_FULL);
		*/


		cv::Mat imgFrame1Copy = imgFrame1.clone();
		cv::Mat imgFrame2Copy = imgFrame2.clone();

		cv::Mat imgDifference;
		cv::Mat imgThresh;

		cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
		cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);

		cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
		cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

		cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);


		cv::imshow("imgDifference", imgDifference);

		cv::threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);

		cv::imshow("imgThresh", imgThresh);

		cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
		cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
		cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
		cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

		cv::dilate(imgThresh, imgThresh, structuringElement5x5);
		cv::dilate(imgThresh, imgThresh, structuringElement5x5);
		cv::erode(imgThresh, imgThresh, structuringElement5x5);

		cv::Mat imgThreshCopy = imgThresh.clone();

		std::vector<std::vector<cv::Point> > contours;

		cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		cv::Mat imgContours(imgThresh.size(), CV_8UC3, SCALAR_BLACK);

		cv::drawContours(imgContours, contours, -1, SCALAR_WHITE, -1);

		cv::imshow("imgContours", imgContours);

		std::vector<std::vector<cv::Point> > convexHulls(contours.size());

		for (unsigned int i = 0; i < contours.size(); i++) {
			cv::convexHull(contours[i], convexHulls[i]);
		}

		for (auto &convexHull : convexHulls) {
			Blob possibleBlob(convexHull);

			if (possibleBlob.boundingRect.area() > 100 &&
				possibleBlob.dblAspectRatio >= 0.2 &&
				possibleBlob.dblAspectRatio <= 1.2 &&
				possibleBlob.boundingRect.width > 15 &&
				possibleBlob.boundingRect.height > 20 &&
				possibleBlob.dblDiagonalSize > 30.0) {
				blobs.push_back(possibleBlob);
			}
		}

		cv::Mat imgConvexHulls(imgThresh.size(), CV_8UC3, SCALAR_BLACK);

		convexHulls.clear();

		

		for (auto &blob : blobs) {
			convexHulls.push_back(blob.contour);
		}

		cv::drawContours(imgConvexHulls, convexHulls, -1, SCALAR_WHITE, -1);

		cv::imshow("imgConvexHulls", imgConvexHulls);

		imgFrame2Copy = imgFrame2.clone();          // get another copy of frame 2 since we changed the previous frame 2 copy in the processing above
		
		
		for (auto &blob : blobs) {                                                  // for each blob
			cv::rectangle(imgFrame2Copy, blob.boundingRect, SCALAR_RED, 2);             // draw a red box around the blob
			//cv::circle(imgLines,  blob.centerPosition, 3, SCALAR_GREEN, -1); 
                        //cv::line(imgLines, blob.centerPosition, blob.centerPosition, cv::Scalar(0, 0, 255), 2);// draw a filled-in green circle at the center
                        //std::cout << "*";

                        // filling an array of all bee positions
                        if(POSITION < CAPACITY){
                            direction[POSITION][0] = blob.centerPosition.y;
                            direction[POSITION][1] = blob.centerPosition.x;
                            a[POSITION] = {blob.centerPosition.y, blob.centerPosition.x};
                            POSITION++;
                        } else {
                            if(!alreadyExecuted){
                                std::cout << "This executes only once!";

                                for(int times = 0; times < 10; times++){
                                    std::sort(a, a + CAPACITY);
                                    for(int i = 0; i < CAPACITY - 1; i++){
                                        a[i] = {(a[i].at(0) + a[i+1].at(0)) / 2 , (a[i].at(1) + a[i+1].at(1)) / 2};
                                    }
                                }


                                for(const auto& s: a) 
                                    cv::line(imgLines, cv::Point(s.at(1), s.at(0)), cv::Point(s.at(1), s.at(0)), cv::Scalar(0, 0, 255), 2);//std::cout << s.at(0) << " " << s.at(1) << "\n";
                                
                                alreadyExecuted = true;
                            }
        
                        }
                            
		}
                
                //std::cout << std::endl;

                imgFrame2Copy = imgFrame2Copy + imgLines;
		cv::imshow("imgFrame2Copy", imgFrame2Copy);

		// now we prepare for the next iteration

		imgFrame1 = imgFrame2.clone();           // move frame 1 up to where frame 2 is


//		if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {       // if there is at least one more frame
//			capVideo.read(imgFrame2);                            // read it
//		}
//		else {                                                  // else
//			std::cout << "end of video\n";                      // show end of video message
//			break;                                              // and jump out of while loop
//		}


		chCheckForEscKey = cv::waitKey(1);      // get key press in case user pressed esc
	}

	if (chCheckForEscKey != 27) {               // if the user did not press esc (i.e. we reached the end of the video)
		cv::waitKey(0);                         // hold the windows open to allow the "end of video" message to show
	}
	// note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows

	return(0);
}