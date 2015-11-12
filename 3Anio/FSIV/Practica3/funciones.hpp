#ifndef FUNCIONES_HPP_
#define FUNCIONES_HPP_

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

using namespace std;
using namespace cv;

void help();

//Creacion filtro butterworth
void butterworth(Mat &filtro, float r, int n);
void shiftDFT(Mat &fImage);
Mat create_spectrum(Mat &complexImg);





#endif