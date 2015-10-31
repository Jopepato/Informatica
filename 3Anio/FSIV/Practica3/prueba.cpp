#include "funciones.hpp"

int main(){

Mat imagen;
float g=1.0;

	 imagen = imread("original.png", -1);
    if(imagen.empty()){
      cout << "Imagen especificada invalida" << endl;
      exit(-1);
    }else{
     /* Mat padded;
      int m = getOptimalDFTSize(imagen.rows);
      int n = getOptimalDFTSize(imagen.cols);
      copyMakeBorder(imagen, padded, 0, m - imagen.rows, 0, n - imagen.cols, BORDER_CONSTANT, Scalar::all(0));

      Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
      Mat complexI;
      merge(planes, 2, complexI);

      dft(complexI, complexI);

      split(complexI, planes);
      magnitude(planes[0], planes[1], planes[0]);
      Mat magI = planes[0];

      magI +=Scalar::all(1);
      log(magI, magI);

      magI = magI(Rect(0,0,magI.cols & -2, magI.rows & -2));

      int cx = magI.cols/2;
      int cy = magI.rows/2;

      Mat q0(magI, Rect(0,0,cx,cy));
      Mat q1(magI, Rect(cx,0,cx,cy));
      Mat q2(magI, Rect(0, cy, cx, cy));
      Mat q3(magI, Rect(cx,cy,cx,cy));

      Mat tmp;
      q0.copyTo(tmp);
      q3.copyTo(q0);
      tmp.copyTo(q3);


      q1.copyTo(tmp);
      q2.copyTo(q1);
      tmp.copyTo(q2);

      normalize(magI, magI, 0, 1, CV_MINMAX);


      //Ahora aplicariamos el filtro butterworth

      //butterworth(magI, 0.5, 2);

      //Mat output = (g+1)*imagen - g*magI;

    imshow("Input Image"       , imagen  );    // Show the result
   	imshow("spectrum magnitude", magI);
   	//imshow("Final", output);
    waitKey();

    //Hacemos la inversa
    idft(magI, magI);

      imshow("Final", magI);
      waitKey(0);

*/

      //Imagen
      imshow("Imagen", imagen);
      waitKey(0);
      Mat fImage;
      imagen.convertTo(fImage, CV_32F);

      Mat fourierTransform;
      dft(fImage, fourierTransform, DFT_SCALE | DFT_COMPLEX_OUTPUT);

      //Do something

      //Aplicamos butterworth
      butterworth(fImage, 0.2, 2);

      //imshow("spectrum magnitude", fourierTransform);
      //waitKey(0);

      Mat inverseTransform;
      dft(fourierTransform, inverseTransform, DFT_INVERSE | DFT_REAL_OUTPUT);

      Mat finalImage;
      inverseTransform.convertTo(finalImage, CV_8U);

      Mat output = imagen;
      unsharp(inverseTransform, imagen, output, 1.5);

      imshow("Final", output);
      waitKey(0);



return 0;
}
}