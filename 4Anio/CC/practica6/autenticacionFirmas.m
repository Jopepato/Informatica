function descifrado = autenticacionFirmas(na, ea, da, nb, eb, db, mens, f)
descifrado = [];
%A cifra el mensaje con la clave publica de B
cif_mens_f = cifro_rsa(eb, nb, mens)
%A cifra su firma con su clave privada
cif_f_da = cifro_rsa(da, na, f)
%Se prepara la firma para ser cifrada con la clave publica de B
%Tenemos que preparar el bloque
tamabloque = length(int2str(na));
aux = [];
%Añadimos ceros necesarios hasta obtener el tamaño de na
for i=1:length(cif_f_da)
    var = num2str(cif_f_da(i));
    while(length(var) < tamabloque)
       var = strcat('0', var); 
    end
    aux = [aux, var];
end
tama = length(num2str(nb))-1;
blo = prepa_num_cifrar(tama, aux);
%A vuelve a cifrar con la clave publica de B
cif_f_da_eb = cifro_rsa_num(eb, nb, blo)

%Ahora pasamos a B
%Descifra el mensaje con su clave privada
descifro_b = descifro_rsa(db, nb, cif_mens_f)
%B descifra la firma cifrada con la clave privada de B
descif_firma_b = descifro_rsa_num(db, nb, cif_f_da_eb)

%Tenemos que preparar el bloque de la firma
aux = prepabloque(na, nb, descif_firma_b);

%B obtiene la firma con la clave publica de A
descif_firma = descifro_rsa(ea, na, aux)