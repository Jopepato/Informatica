function [amplio, f_chica, c_chica] = escondo_img(fotochica, fotocobertura)

%Escondemos una imagen pequeña en otra imagen más grande
matrizImagenChica = imread(fotochica);
matrizImagenCobertura = imread(fotocobertura);
[rows, cols, capas] = size(matrizImagenCobertura);
%Ahora metemos la imagen pequeña en la grande
for i=1:capas
    [amplio, f_chica(:,:,i)] = modificamos_img(matrizImagenCobertura(:,:,i), matrizImagenChica(:,:,i), 1);
end
c_chica = size(matrizImagenChica,1) * size(matrizImagenChica,2) * 8;
imshow(f_chica);
imwrite(f_chica, 'matriz_con_oculta.bmp');