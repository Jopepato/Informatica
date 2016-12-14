function [amplio, matriz_mod] = modificamos(matriz, texto, ini_filas, col)
%Pasamos el texto a ese numero de columnas
[amplio, texto_bit] = textobit_col(texto, col);

%Una vez tenemos eso, recorremos la matriz con la matriz de texto_bit y
%vamos modificando
matriz_mod = matriz;
ini_filas = ini_filas-1;
for i=1:size(texto_bit, 1)
   for j=1:col
       if texto_bit(i,j) == '1' && mod(matriz(aux, j), 2) == 0
          %Sumamos 1 a la matriz
          aux = i + ini_filas;
          matriz_mod(aux, j) = matriz(aux, j) +1;
       else
           aux = i + ini_filas;
           if mod(matriz(aux, j), 2) ~=0
               matriz_mod(aux, j) = matriz(aux, j) -1;
           end
       end
   end
end