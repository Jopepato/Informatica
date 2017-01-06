function desorden_pixel(foto, A)

matrizCopia = foto;

[fil, col, capas] = size(foto);

%Recorremos la matriz entera y empezamos a intercambiar las posiciones
% de la matriz
for i=1:fil
    for j=1:col
        coord = mod(A*[i;j], fil);
        x=coord(1);
        y=coord(2);
        if(x==0)
            x=fil;
        end
        if(y==0)
            y=col;
        end
        %Tenemos que mirar lo de las 3 capas
        if(capas>1)
            matrizCopia(i,j,1:3)=foto(x,y,1:3);
        else
            matrizCopia(i,j,1) = foto(x,y,1);
        end
    end
end

setappdata(gcf, 'imagenDesordenada', matrizCopia);