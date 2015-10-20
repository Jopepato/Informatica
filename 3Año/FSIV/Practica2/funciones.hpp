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
void rellenaVector(vector<double> &v);
void vectorAcumulado(vector<double> &v);
void calcHistograma(const Mat &imagen, vector<double> &histograma, int r);
void calcHistogramaMascara(const Mat &imagen,const Mat &mascara, vector<double> &histograma, int r);
void normalizaVector(vector<double> &v);
void ecualizar(Mat &imagen, vector<double> &v, int r);
void ecualizarMascara(Mat &imagen,const Mat &mascara, vector<double> &v, int r);


#endif
