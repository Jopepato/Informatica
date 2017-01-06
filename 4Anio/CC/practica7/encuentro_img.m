function encuentro_img(c_chica, f_chica, fotogrande_mod)

matrizImagen = imread(fotogrande_mod);
[rows, cols, capas] = size(matrizImagen);
elementos = c_chica * f_chica * 8;
admas = mod(elementos, cols);

fin_filas = floor(elementos/cols)+1;
for i=1:capas
    vector_bit = obtengo_bit(matrizImagen(:,:, i), 1, fin_filas, admas);
    matriz_bit = reshape(vector_bit, 8, [])';
    matriz_numeros(:,:,i) = bin2dec(matriz_bit);
end
[rowsM, colsM, capsM] = size(matriz_numeros);
for i=1:3
    mAux = matriz_numeros(:,:,i);
    matriz_final(:,:,i) = uint8(reshape(mAux, f_chica, c_chica))';
end
imshow(matriz_final(:,:,1:3));