function [amplio, f_chica, c_chica] = escondo_img(fotochica, fotocobertura)

%Escondemos una imagen pequeña en otra imagen más grande
matrizImagenChica = imread(fotochica);
matrizImagenCobertura = imread(fotocobertura);

%Ahora metemos la imagen pequeña en la grande
[amplio, f_chica] = modificamos_img(matrizImagenCobertura(:,:,1:3), matrizImagenChica(:,:,1:3), 1);
c_chica = size(matrizImagenChica,1) * size(matrizImagenChica,2) * 8;
imwrite(f_chica, 'matriz_con_oculta.bmp');