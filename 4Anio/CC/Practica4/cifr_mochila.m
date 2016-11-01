function cifrado = cifr_mochila(s, texto)
%Con esta funcion ciframos gracias a la mochila
%Se podra cifrar aunque la mochila no sea supercreciente

ascii = double(texto) %Esto creará un vector con los numeros en ascii de las letras
bin = dec2bin(ascii, 8) %Aqui ya tendremos un vector con los numeros en binario

%Ahora tenemos que dividir los bits en grupos
bin = reshape(bin', 1, [])
%Ahora le añadimos los 1 que falten
d = length(s);
a = mod(size(bin,2), d);
if(a ~= 0)
    %Si no es divisible metemos 1 al final
    for i=1:d-a
       bin = [bin, '1'];
    end
end
%Asi ya lo tenemos lleno de 1 y le hacemos el reshape
bin = reshape(bin,length(s), [])'
%Y ahora lo ciframos
cifrado = [];
aux = 0;
for i=1:size(bin,1)
    for j=1:size(bin,2)
       if(bin(i,j) == '1')
            aux = aux + s(j);
       end
    end
    cifrado = [cifrado, aux];
    aux = 0;
end