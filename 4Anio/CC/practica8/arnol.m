function imagen = arnol(foto, A)

%Comprobamos que la matriz A es cuadrada y 2x2

[filasA, columA] = size(A);
if filasA == 2 && columA == 2
   
    %Ahora tenemos que comprobar que las filas sean iguales a las columnas
    %de foto
    matrizFoto = imread(foto);
    [filasFoto, columFoto, capas] = size(matrizFoto);
    %Recortamos la foto
    if columFoto-1 <filasFoto-1
        nuevaFoto = matrizFoto(1:columFoto-1, 1:columFoto-1, 1:3);
    else
        nuevaFoto = matrizFoto(1:filasFoto-1, 1:filasFoto-1, 1:3);
    end
    
    %imshow(nuevaFoto);
    
    desorden_pixel(nuevaFoto, A);
    imagen = getappdata(gcf, 'imagenDesordenada');
    imshow(imagen);
    imwrite(imagen, 'fotoDesordenada.bmp')
    
else
    disp('La matriz A no es cuadrada y no se puede aplicar el metodo');
end