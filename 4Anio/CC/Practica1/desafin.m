function descifradoafin = desaafin(clave, d, texto)
numero = letranumero(texto);
cifradoafin = [];
    abecedario = 'abcdefghijklmnnopqrstuvwxyz';
    abecedario(15) = char(241);

if gcd(clave, length(abecedario)) == 1
   [G, U, V]= gcd(length(abecedario), clave);
    numero =  V * (numero - d);
    numero = mod(numero, length(abecedario));
    

else
    error('ErrrorTest:convertTest', 'El maximo comun divisor no es 1')
    
end

    descifradoafin = numeroletra(numero);