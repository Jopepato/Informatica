function [numero, amplio] = bitmenos(texto, foto)

matrizImagen = imread(foto);
[filasFoto, columFoto, capas] = size(matrizImagen);
numero = length(texto)*8;
[amplio, matriz_mod] = modificamos(matrizImagen(:,:,1), texto, 1, columFoto);
%Y ahora guardamos la imagen
matriz_mod(:,:,2:3) = matrizImagen(:,:,2:3);

imwrite(matriz_mod, 'imagen_modificada.png');