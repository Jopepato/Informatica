function cripto_shamir_zippel(cp, mu)

%Se calcula q, que es S1/S2 mod mu
%Para ello tendremos que calcular 
tic
[G, U, V] = gcd(cp(2), mu);
q = mod(cp(1) * V, mu);
m = length(cp)+1;
CM = [];
salirRango = false;
while salirRango==false
    j=0;
    rango = 2^(m+j);
    fprintf('Vamos a buscar en el rango [1 %d]\n', rango);
    %Vamos rellenando ese vector con los múltiplos modulares
    for i=1:rango
       CM = [CM, mod(i * q, mu)];
    end
    CM = sort(CM);
    %El candidato para S1' sera el menor valor de esa sucesión de numeros que
    %hemos calculado, por ello hemos ordenado la mochila
    i = 1;
    salir = false;
    while salir==false
    S1 = CM(i);
    S1
            %Seguimos por aqui porque el mcd entre s1' y mu es 1, por lo que
            %podremos seguir
            [G, U, V] = gcd(S1, mu);
            V
            w = mod(S1 * V, mu);
            w
            %Una vez tenemos w, calculamos w inverso y ya podremos sacar la
            %mochila.
            [G, U, winv] = gcd(mu, w);
            winv
            s1 = mod(cp * winv,mu)
            %Una vez tenemos la mochila, comprobamos que es supercreciente, si
            %es supercreciente hemos terminado
            if mochila(s1) == 1
                salir = true;
                salirRango = true;
                disp('Ya hemos encontrado la mochila');
                s1
                return;
            end
        i = i+1;
        if i>length(CM)
            salir=true;
        end
    end
    j= j+1;
end
toc