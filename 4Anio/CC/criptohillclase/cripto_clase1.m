function matrizclave=cripto_clase1(claro,cripto,m)
%m es el orden de la matriz
matrizclave=[];
claro=letranumero(claro);
cripto=letranumero(cripto);
nclaro=length(claro);
ncripto=length(cripto);
    aux = ncripto - nclaro;
    claro = [claro, zeros(1,aux)+23];
    nclaro = length(claro);
if nclaro >= m*m
    % PONER EL TEXTO CLARO Y EL CIFRADO EN FILAS DE m columnas,

    
    claro=reshape(claro,m,[])';
    crip=reshape(cripto,m,[])';
    % HACEMOS OPERACIONES ELEMENTALES HASTA  QUE LA MATRIZ DEL TEXTO CLARO SEA I
    for j=1:m
        [G,AA,B]=gcd(27,claro(j,j));
        if G == 1
            %EL PIVOTE,LO HACEMOS 1 MULTIPLICANDO  LA FILA POR SU INVERSO
            inv11=mod(B,27);
            claro(j,:)=mod(inv11*claro(j,:),27);
            crip(j,:)=mod(inv11*crip(j,:),27);
            %HACEMOS CEROS DEBAJO Y ENCIMA DEL PIVOTE
            for i=1:(nclaro/m)
                if i~=j
                    crip(i,:)=mod(crip(i,:)-claro(i,j).*crip(j,:),27);
                    claro(i,:)=mod(claro(i,:)-claro(i,j).*claro(j,:),27);
                end
            end
        else
           %Cuando no tiene inverso cambiamos filas
           for k=j+1:nclaro/m
              aux = claro(k, j);
              [G, AA, B] = gcd(27, claro(k,j));
              if G == 1
                  fila = claro(k, :);
                  claro(k, :) = claro(j,:);
                  claro(j, :) = fila;
                  fila = crip(k, :);
                  crip(k, :) = crip(j, :);
                  crip(j, :) = fila;
                  break
              end
              if G ~= 1
                error('ErrorTests:convertTest','la matriz no es valida')
              end
           end
        end
    end
    matrizclave=crip(1:m,:)';
else
   disp('No se puede criptoanalizar con un texto claro tan pequeño') 
end

