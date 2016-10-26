function matrizclave = cripto_hill(textoclaro, textocifrado, orden)

%Pasamos el texto a numero y creamos las matrices para hacer el
%criptoanalisis


%Metemos x al final para poder hacer despues el reshape
aux = mod(length(textoclaro), orden);
    if(aux~= 0)
        for i=1:(orden-aux)
            textoclaro = strcat(textoclaro, 'x');
        end
    end
    
numerosClaro = letranumero(textoclaro)
numerosCifrado = letranumero(textocifrado);

Y = reshape(numerosCifrado, orden, []);
X = reshape(numerosClaro, orden, []);

Y = Y';
X = X';

for i=1:orden
    aux = X(i,i);
    [G, U, V] = gcd(27, aux);
    %Si el elemento tiene inverso, hacemos 0 tanto en las filas de arriba
    %como en las de abajo.
    %Si no tiene inverso, buscamos uno e intercambiamos filas.
    if G == 1
        %Tiene inverso
        X(i, :) = mod(X(i,:)*V, 27);
        Y(i, :) = mod(Y(i,:)*V, 27);
        %Una vez tenemos 1 en el (i,i) Hacemos 0s en la columna i, pero en
        %todas las filas tanto por encima como por debajo
        for j=1:size(X,1)
            if j~=i
                %Hacemos ceros
                aux2 = X(j,i);
                X(j, :) = mod(X(j,:)-aux2*X(i,:),27);
                Y(j, :) = mod(Y(j,:)-aux2*Y(i,:),27);
            end
            
        end
    else
        %Si no tiene inverso, tenemos que buscar el primer numero de las
        %filas de abajo que tenga e intercambiarlo
        for k=i+1:size(X,1)
            [G, U, V] = gcd(27, X(k, i));
            if G == 1
                %ese numero tiene inverso, asi que intercambiamos filas y
                %nos salimos de este bucle
                fila = X(i, :);
                X(i, :) = X(k, :);
                X(k, :) = fila;
                %Ahora lo mismo con la matriz Y
                fila = Y(i, :);
                Y(i, :) = Y(k, :);
                Y(k, :) = fila;
                break
            end
        end
    end
    
end

%Despues de estas operaciones ya tenemos las dos matrices.
%Ahora cogeremos la matriz clave de la matriz Y
matrizclave = Y(1:orden,1:orden);
matrizclave = matrizclave';

