function potencia = arnol_02(foto, A)
%Vamos a desordenar una imagen desordenada para obtener su imagen original
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
            nuevaFoto = matrizFoto(1:columFoto, 1:columFoto, 1:3);
        else
            nuevaFoto = matrizFoto(1:filasFoto, 1:filasFoto, 1:3);
        end
    else
        nuevaFoto = matrizFoto;
    end

opcion = input('Caso 1 o 2: ');
%Cargamos la foto
switch opcion
    case 1
       %Averiguamos la potencia de A, que será las veces que desordenaremos
       %dicha imagen
       potencia = pote(A, filasFoto);
       %Le pedimos al usuario el numero de veces que quiere desordenar
       potencia
       usuario = input('Numero de veces que quieres desordenar, menor que potencia')
       auxFoto = nuevaFoto;
       for i=1:potencia-usuario
           desorden_pixel(auxFoto, A)
           auxFoto = getappdata(gcf, 'imagenDesordenada');
       end
       imshow(auxFoto);
       imwrite(auxFoto, 'FotoOrdenadaArnol2.bmp')
    case 2
        %Iremos desordenando una por una, mientras el usuario quiera
        salir = 1;
        auxFoto = nuevaFoto;
        potencia = 1;
        while salir~=0
            %Desordenamos y mostramos
            desorden_pixel(auxFoto, A);
            potencia = potencia +1;
            auxFoto = getappdata(gcf, 'imagenDesordenada');
            imshow(auxFoto);
            salir = input('Repetir 1, salir 0: ');
        end
        %Y ahora guardamos la imagen
        imwrite(auxFoto, 'FotoOrdenadaArnol2.bmp')
        
end
end