function [amplio, matriz_cob_modi] = modificamos_img(matriz_cob, matriz, ini_fila)
%Tenemos que comprobar si en la matriz de cobertura hay espacio para la
%matriz a ocultar

[rowsMa, colsMa] = size(matriz);
[rowsCob, colsCob] = size(matriz_cob);
tamaMatriz = rowsMa * colsMa * 8;
tamaCob = rowsCob * colsCob * 8;

if tamaMatriz > tamaCob
    error('Matriz de cobertura insuficiente para guardar el mensaje');
else
    %Metemos la matriz en la de cobertura
    %Primero pasamos dicha matriz a bits
    [amplio, matriz_bit] = matrizbit_col(matriz, colsCob);
    %Una vez tenemos dicha matriz ya la guardamos en la otra
    matriz_cob_modi = matriz_cob;
    ini_fila = ini_fila-1;
    for i=1:size(matriz_bit, 1)
        for j=1:colsCob
            if matriz_bit(i,j) == '1' && mod(matriz_cob(aux, j), 2) == 0
                %Sumamos 1 a la matriz
                aux = i + ini_fila;
                matriz_cob_modi(aux, j) = matriz_cob(aux, j) +1;
            else
                aux = i + ini_fila;
                if mod(matriz_cob(aux, j), 2) ~=0
                    matriz_cob_modi(aux, j) = matriz_cob(aux, j) -1;
                end
            end
        end
    end
end
