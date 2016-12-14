function mensaje = des_bitmenos(numero, fotomens)

%Recorremos la matriz sabiendo el número de pixeles que debemos de mirar

mensaje=[];
image=imread(fotomens);
rojos=image(:,:,1);
[rows,cols, canales]=size(rojos);
matriz_bit=dec2bin(rojos');
for i = 1:numero
    aux=matriz_bit(i,8);
    mensaje=[mensaje,aux];
end
mensaje=reshape(mensaje,8,[]);
mensaje=mensaje';
mensaje=bin2dec(mensaje);
mensaje=char(mensaje);
mensaje=mensaje';