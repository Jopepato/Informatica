function descifrado = descifro_rsa(d, n, cifrado_numeros)

descifro_numeros = descifro_rsa_num(d, n, cifrado_numeros);

descifrado = num_descifra(n, descifro_numeros);