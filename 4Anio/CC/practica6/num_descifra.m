function desci = num_descifra(n, bloque_numero)
%Pasamos ese bloque de numeros a letras

tama = length(num2str(n))-1;
nuevoBloque = [];
for i=1:length(bloque_numero)
    aux = num2str(bloque_numero(i));
    if length(aux) < tama
        while 1
           if mod(length(aux), tama) == 0
               %Ese numero ya es del tamaño de tama
               break;
           else
              aux = strcat('0', aux);
           end
        end
    end
    nuevoBloque = [nuevoBloque, aux];
end
%Con esto ya hemos metido los 0s al principio de cada número
%Quitamos el 0 que añadimos al final, si se añadió
if mod(length(nuevoBloque),2) ~= 0
    nuevoBloque = nuevoBloque(1:length(nuevoBloque)-1)';
end
nuevoBloque = reshape(nuevoBloque, 2, [])';
%Agrupamos los numeros de dos en dos y los pasamos a numeros
numeros =[];
for i=1:length(nuevoBloque)
   numeros = [numeros, str2num(nuevoBloque(i,:))]; 
end

%Ahora quitamos los 30 del final
nuevosNumeros = [];
for i=1:length(numeros)
   if numeros(i) ~= 30
       nuevosNumeros = [nuevosNumeros, numeros(i)];
   end
end
desci = numeroletra(nuevosNumeros);