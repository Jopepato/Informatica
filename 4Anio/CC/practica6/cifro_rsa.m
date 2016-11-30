function cifrado = cifro_rsa(e, n, texto)

bloque = letra2numeros(texto);
aux = num2str(n);
tama = length(aux) -1;
blo = prepa_num_cifrar(tama, bloque);
cifrado = [];
for i=1:length(blo)
    cifrado = [cifrado, potencia(blo(i), e, n)];
end