function desorden_pixel(foto, A)

matrizCopia = foto;

[fil, col, capas] = size(foto);

%Recorremos la matriz entera y empezamos a intercambiar las posiciones
% de la matriz
for i=1:fil
    for j=1:col
        coord = mod(A*[i;j], fil);
        x=coord(1)+1;
        y=coord(2)+1;
        matrizCopia(i,j,1:3)=foto(x,y,1:3);
    end
end

setappdata(gcf, 'imagenDesordenada', matrizCopia);