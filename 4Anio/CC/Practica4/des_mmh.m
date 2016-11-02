function des_mmh(s1, cifrado, mu, invw)

cifrado = mod(cifrado*invw, mu);
%Y ahora llamamos al descifrar con el cifrado bueno

mensaje = des_mochila(s1, cifrado);