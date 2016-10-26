function [texto, cifrado] = cifro_permutacion(p, texto)

%Comprobamos que la permutacion es válida y le hacemos su matriz, dicha
%matriz se la pasamos a alcifrado hill y este ya nos cifra



if permutacion_v(p) == 1
    %La permutacion es valida por lo tanto podemos continuar
    A = matper(p);%Matriz de la permutacion
    %Ahora ciframos con la matriz de permutacion y el cifrado hill
    d = size(A, 1);

    %Comprobamos que el texto es divisible entre el numero de filas o
    %columnas de A
    a = mod(length(texto), d);
    numeros = letranumero(texto);
    
    if(a ~= 0)
        %Si no es divisible metemos W al final
        for i=1:(d-a)
           numeros = [numeros, 23];
        end
    end
    
    X = reshape(numeros, d, []);
    Y = mod(A*X, 27);
    %Ahora tenemos que concatenar las columnas y pasarlo a letra

    cifrado = reshape(Y, 1, []);

    %Con esto ya deberiamos de tener el texto cifrado
    cifrado = numeroletra(cifrado);
        
else
    error('ErrorTests:convertTest','Permutacion no valida')
end