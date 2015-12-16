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
#include <fstream>

using namespace std;
using namespace cv;

struct parametrosRotatedRectangle{
	float angulo;
	Point2f centro;
	Size2f size;
};

struct parametrosBoundingBox{

};


struct parametros{
	double longitud;
	double diametro;
	RotatedRect rectanguloBasico;
	double excentricidad;
	double area;
	Rect ocupacion;
	double compacidad;
	double ocupaConvex;
	double solidez;
	struct parametrosRotatedRectangel rotatedRectangle;
	struct parametrosBoundingBox boundingBox;

};


void help();
void contornoAFichero(const vector<Point> &contorno, const string &nombreFichero);

void seleccionaMayorContorno(const vector<vector<Point> >&contours, vector<Point> &contorno);

void calculaParametros(struct parametros &params, const vector<Point> &contorno);

void muestraParametros(struct parametros params);


#endif