function des_mmh(s1, cifrado, mu, invw)

%Con estos datos obtenemos la clave privada y descifrada

s2 = [];
for i=1:length(s1)
    s2 = [s2,mod(invw * s1(i), mu)]
end

%Y ahora llamamos al descifrar con la clave ya publica

mensaje = des_mochila(s2, cifrado);