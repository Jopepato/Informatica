function desci = num_descifra(n, bloque_numero)
%Pasamos ese bloque de numeros a letras
bloque_strings = [];
for i=1:length(bloque_numero)
    bloque_strings =[bloque_strings, num2str(bloque_numero(i))];
end
tama = length(num2str(n))-1;

for i=1:length(bloque_strings)
    if length(bloque_strings(i)) < tama
        while 1
           if mod(length(bloque_strings), tama) == 0
               %Ese numero ya es del tamaño de tama
               break;
           else
                bloque_strings(i) = strcat('0', bloque_strings(i));
           end
        end
    end
end
%Con esto ya hemos metido los 0s al principio de cada número

%Quitamos el 0 que añadimos al final, si se añadió

%Agrupamos los numeros de dos en dos y los pasamos a numeros
desci = []
bloque = reshape(bloque_strings, 2, [])'
