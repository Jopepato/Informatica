function [texto, cifrado] = cifro_permutacion(p, texto)

%Comprobamos que la permutacion es válida y le hacemos su matriz, dicha
%matriz se la pasamos a alcifrado hill y este ya nos cifra



if permutacion_v(p) == 1
   %Podemos permutar 
   A = matper(p);
   
   d = size(A, 1);
       %Comprobamos que el texto es divisible entre el numero de filas o
       %columnas de A
       a = mod(length(texto), d);
       if a ~= 0
            %Si no es divisible metemos X al final
            for i=1:d-a
               texto = strcat(texto, 'x');
            end
       end
        %Pasamos el texto a numeros y lo dividimos en grupos
        numeros = letranumero(texto);
        X = reshape(numeros, d, []);
        Y = mod(A*X, m);
        for i=size(Y,1)
            cifrado = strcat(cifrado, numeroletra(Y(:,i)));
        end
else
    error('ErrorTests:convertTest','La permutacion introducida no es válida\n',m)
end