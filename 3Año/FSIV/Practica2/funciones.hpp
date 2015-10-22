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
void calcHistograma(const Mat &imagen, vector<double> &histograma);
void calcHistogramaMascara(const Mat &imagen,const Mat &mascara, vector<double> &histograma);
void normalizaVector(vector<double> &v);
void ecualizar(Mat &imagen, vector<double> &v);
void ecualizarMascara(Mat &imagen,const Mat &mascara, vector<double> &v);

void ecualizarRadio(Mat &imagen, vector<double> &v, int x, int y);
void ecualizarMascaraRadio(Mat &imagen, const Mat &mascara, vector<double> &v, int x, int y);


#endif
