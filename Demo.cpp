#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <time.h>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;




int main()
{
  std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;

  /* Open video file */
  VideoCapture capture(0);
  if(!capture.isOpened()){
    std::cerr << "Cannot open video!" << std::endl;
    return 1;
  }

  

  //MOG2 mask
  Mat fgMaskMOG2;
  Ptr<BackgroundSubtractor> pMOG2;

  std::cout << "Press 'q' to quit..." << std::endl;
  int FrameCount = 0;
  int key = 0;
  Mat frame;
  int framecount=0;
  double t = NULL;
  VideoWriter inputWrite;
  inputWrite.open("input.avi",-1,24,Size(640,360));
  if(!inputWrite.isOpened()){
	  std::cout<<"write not opened"<<endl<<endl;
  }
  VideoWriter outputWrite;
  outputWrite.open("output.avi",-1,24,Size(640,360));
  if(!outputWrite.isOpened()){
	  std::cout<<"write not opened"<<endl<<endl;
  }

  double ttime = (double)getTickCount();

  Mat previous_frame, current_frame, next_frame;

  pMOG2 = createBackgroundSubtractorMOG2(500,12,false);
  
  capture.read(current_frame);

  while(key != 'q')
  {
    cv::Mat img_mask;
    pMOG2->apply(current_frame, fgMaskMOG2);
	if(!fgMaskMOG2.empty())
    {
		outputWrite << fgMaskMOG2;
    }
	inputWrite<<current_frame;
	FrameCount++;
	if(capture.read(current_frame)){
		key=waitKey(1);
	}
	else{
		key='q';
		break;
	}
		

   
  }

  ttime = ((double)getTickCount() - t)/getTickFrequency();
  double ftime = (ttime / FrameCount);
  std::cout<< "Number for frames: " << FrameCount << endl;
  std::cout<< "Total Time in milliseconds: " << ttime << endl;
  std::cout << "Milliseconds per frame: " << ftime << endl << endl << endl << endl;

  inputWrite.release();
  outputWrite.release();
  cvDestroyAllWindows();
  capture.release();
  
  return 0;
}
