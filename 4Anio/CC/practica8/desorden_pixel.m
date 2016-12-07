function desorden_pixel(foto, A)

matrizCopia = foto;

[fil, col, capas] = size(foto);

%Recorremos la matriz entera y empezamos a intercambiar las posiciones
% de la matriz
for i=1:fil
   for j=1:fil
       aux = [i; j];
       nuevaPos = mod(A*aux, fil);
       matrizCopia(nuevaPos(1)+1, nuevaPos(2)+1, 1:3) = foto(i, j, 1:3);
   end
end

setappdata(gcf, 'imagenDesordenada', matrizCopia);