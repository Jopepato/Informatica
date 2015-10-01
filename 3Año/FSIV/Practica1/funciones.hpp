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




void estadisticosMask(const cv::Mat &matriz,const cv::Mat &mascara, const int fil, const int col);
void estadisticos(const cv::Mat &matriz, const int fil, const int col);
void usaMascara(cv::Mat &matriz, const cv::Mat &mascara);

#endif