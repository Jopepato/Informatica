function [frecuencia, freordenada] = cripto_ana_orden(v)
    abecedario = 'abcdefghijklmnñopqrstuvwxyz';
    m = length(abecedario);
    frecuencia = zeros(27,2);
    numeros = letranumero(v);

    for i=1:m
        aux = (numeros==i-1);
        frec = sum(aux);
        frecuencia(i,1) = frec/length(v);
        frecuencia(i,2) = floor(i-1);
    end
    
    freordenada = sortrows(frecuencia, -1);
    