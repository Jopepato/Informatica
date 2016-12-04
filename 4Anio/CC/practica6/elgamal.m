function descifrado = elgamal(q, g, texto)

%Clave privada será a y la publica sera publi_a
a = randi([1 q-1], 1);
publi_a = potencia(g, a, q);

%Calculamos k 
k = randi([1 q-1], 1);
gk = potencia(g, k, q);
gak = potencia(g, a*k, q);

%Preparamos el bloque para cifrar
tama = length(int2str(q))-1;
doble = letra2numeros(texto);
blo = prepa_num_cifrar(tama, doble);

%B envia el par a A
y1 = gk;
y2 = [];
for i=1:length(blo)
    y2 = [y2, mod(uint64(blo(i)*gak), q)];
end

%A descifra
invyla = potencia(y1, a, q);
[g, c, d] = gcd(int64(q), int64(invyla));
invyla = mod(d, q);
descifro = mod(uint64(y2*uint64(invyla)), q);
descifrado = num_descifra(q, descifro);