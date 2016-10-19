function numero = letranumero(texto)
    abecedario = 'abcdefghijklmnñopqrstuvwxyz';
    texto = lower(texto);
    numero = [];
    m = length(texto);
    n = length(abecedario);
    for i=1:m
       for j=1:n
           if(texto(i) == abecedario(j))
               numero = [numero, j-1];
               break
           end
       end
    end