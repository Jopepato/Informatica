function cifrado = cifro_rsa_num(e, n, blo)
%Esta función es igual que la función de cifrar RSA pero nos dan
%directamente el bloque de números, así que solo tendremos que aplicar la
%potencia

cifrado = []
for i=1:length(blo)
    cifrado = [cifrado, potencia(blo(i), e, n)];
end