function [n, d, e] = genero_clave(p, q)
%En esta funcion calcularemos la clave publica y clave privada

%elegir dos primos grandes
n = p*q;
fiden = (p-1)*(q-1);

%Ahora calulamos un numero e y d
while 1
    e = randi([1 fiden-1]);
    %Averiguamos si es coprimo con fiden y
    %también nos quedaremos con el inverso
    [g, c, d] = gcd(e, fiden);
    if g == 1
       break; 
    end
end

d = mod(d, fiden);

fprintf('La clave privada es (%d, %d)\n', n,d);
fprintf('La clave pública es (%d, %d)\n\n', n, e);