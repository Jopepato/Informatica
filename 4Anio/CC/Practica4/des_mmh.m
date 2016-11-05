function des_mmh(s1, cifrado, mu, invw)

%Multiplicamos el cifrado por la inversa de w para obtener la clave privada
%que será la utilizada para descifrar
cifrado = mod(cifrado*invw, mu);
%Y ahora llamamos al descifrar con el cifrado bueno
mensaje = des_mochila(s1, cifrado);