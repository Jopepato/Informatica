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

void unsharp(Mat &imagen, Mat &imagenPasoBaja, float g);
void unsharp(Mat &image, Mat &imagenPasoBaja, Mat &mascara, float g);
void butterworth(Mat &imagenPasoBaja, int r, int n);
void butterworthMascara(Mat &imagenPasoBaja, Mat &mascara, int r, int n);





#endif