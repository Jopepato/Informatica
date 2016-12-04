function descifro_num = descifro_rsa_num(d, n, cifrado_numeros)

%Tenemos que hacerle la potencia con la clave privada
descifro_num = [];
for i=1:length(cifrado_numeros)
   descifro_num = [descifro_num, potencia(cifrado_numeros(i), d, n)]; 
end