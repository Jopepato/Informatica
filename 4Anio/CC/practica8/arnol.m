function imagen = arnol(foto, A)

%Comprobamos que la matriz A es cuadrada y 2x2

[filasA, columA] = size(A);
if filasA == 2 && columA == 2
   
    %Ahora tenemos que comprobar que las filas sean iguales a las columnas
    %de foto
    matrizFoto = imread(foto);
    [filasFoto, columFoto, capas] = size(matrizFoto);
    %Miramos si la foto es cuadrada
    if filasFoto ~= columFoto
        %Recortamos la foto
        if columFoto <filasFoto
            nuevaFoto = matrizFoto(1:columFoto-1, 1:columFoto-1, :);
        else
            nuevaFoto = matrizFoto(1:filasFoto-1, 1:filasFoto-1, :);
        end
    else
        nuevaFoto = matrizFoto;
    end
    %Ahora miraremos la opcion, si es 0, lo que se hace es desordenar, si
    %es 1 se ordena
    opcion = input('1 Para desordenar, 2 para ordenar: ');
    switch opcion
        case 1
            desorden_pixel(nuevaFoto, A);
            imagen = getappdata(gcf, 'imagenDesordenada');
            imshow(imagen);
            imwrite(imagen, 'imagenDesordenada.bmp')
    
        case 2
            invA = inv_modulo(A, size(nuevaFoto,1));
            desorden_pixel(nuevaFoto, invA);
            imagen = getappdata(gcf, 'imagenDesordenada');
            imshow(imagen);
            imwrite(imagen, 'imagenOrdenada.bmp');
    end
else
    disp('La matriz A no es cuadrada y no se puede aplicar el metodo');
end