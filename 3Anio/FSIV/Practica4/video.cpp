#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>

using namespace cv;
using namespace std;

int main(int argc, char ** argv){

string nombreVideo = argv[1];

VideoCapture cap(nombreVideo);

if(!cap.isOpened()){
	cout << "Video especificado invalido" << endl;
	exit(-1);
}

    Mat edges;
    //namedWindow("edges",1);
    while(true){
        Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, CV_BGR2GRAY);
        imshow("frames", frame);
        if(waitKey(30) >= 0) break;
    }

cap.release();

return 0;

}
