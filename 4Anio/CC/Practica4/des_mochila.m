function mensaje = des_mochila(s, cifrado)

%Funcion para descifrar la mochila

%Obtenemos los vectores de bit
aux = [];
for i=1:size(cifrado,2);
   aux2 = sol_mochila(s, cifrado(i));
   aux = [aux, aux2];
end
%Ya tenemos el vector con la secuencia de bits

%Ahora tenemos que quitarle los ultimos elementos para que sea divisible
%por 8
b = mod(length(aux), 8);
if b ~= 0
   a = length(aux) - b;
   aux = aux(1:a);
end
%Ahora ya es multiplo de 8
aux = reshape(aux, 8,[])';
%ahora lo pasamos a decimal
dec = bin2dec(num2str(aux));
mensaje = [char(dec)]';