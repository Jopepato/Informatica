function [amplio, matriz_bit] = matrizbit_col(matriz, col)

%Recorremos la matriz de numeros y vamos guardando cada elemento en un
%array
matriz = mod(matriz, 256);
arrayBits = [];
for i=1:size(matriz, 1)
   for j=1:size(matriz, 2)
      arrayBits = [arrayBits, dec2bin(matriz(i,j), 8)];
   end
end
amplio = 0;
if mod(length(arrayBits), col) ~= 0
    
    for i=1:col - mod(length(arrayBits), col)
       arrayBits = [arrayBits, '0'];
       amplio = amplio +1;
    end
else
    amplio = 0;
end
matriz_bit = reshape(arrayBits, col, [])';