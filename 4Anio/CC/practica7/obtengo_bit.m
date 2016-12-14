function obten = obtengo_bit(matriz, ini_filas, fin_filas, admas)

%Obtengo los bits menos significativos de una matriz dada
[rows, cols] = size(matriz);
obten = [];
for i=ini_filas:fin_filas
   for j=1:cols
       if i == fin_filas
          %Aqui tenemos que llegar hasta el numero de admas
          if j> admas
              break;
          end
       end
       %Metemos el ultimo bit en el vector
       aux = dec2bin(matriz(i,j), 8);
       obten = [obten, aux(8)];
   end
end