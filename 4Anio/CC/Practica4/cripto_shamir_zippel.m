function cripto_shamir_zippel(cp, mu)

%Se calcula q, que es S1/S2 mod mu
%Para ello tendremos que calcular 
tic
%Buscamos el inverso de b2
[G, U, V] = gcd(cp(2), mu);
q = mod(cp(1) * V, mu);
m = length(cp)+1;
CM = [];
salirRango = false;
j=0; %Con esta variable j controlaremos el rango
while salirRango==false
    rango = 2^(m+j);
    fprintf('Vamos a buscar en el rango [1 %d]\n', rango);
    %Vamos rellenando ese vector con los múltiplos modulares
    for i=1:rango
       CM = [CM, mod(i * q, mu)];
    end
    CM = sort(CM);
    %El candidato para S1' sera el menor valor de esa sucesión de numeros que
    %hemos calculado, por ello hemos ordenado la mochila y la recorreremos
    %en orden ascendente
    for i=1:length(CM)
    S1 = CM(i);
            %Seguimos por aqui porque el mcd entre s1' y mu es 1, por lo que
            %podremos seguir, esta era una condicion fuerte que no siempre
            %se cumple porque nuestro programa puede tener exito aunque
            %dicha condición no se cumpla
            [G, U, V] = gcd(mu, S1);
            w = mod(cp(1) * V, mu);
            %Una vez tenemos w, calculamos w inverso y ya podremos sacar la
            %mochila.
            [G, U, winv] = gcd(mu, w);
            %Aplicamos winv a toda la mochila
            s1 = mod(cp * winv,mu);
            %Una vez tenemos la mochila, comprobamos que es supercreciente, si
            %es supercreciente hemos terminado
            if mochila2(s1) == 1
                disp('Ya hemos encontrado la mochila');
                disp(s1);
                toc
                return;
            end
    end
    %Aqui le pedimos al usuario si desea ampliar el rango
    prompt = 'Mochila no encontrada en dicho rango, si desea ampliar el rango pulse 1, en caso contrario 0: ';
    aux = input(prompt);
    if aux==1
        j = j+1;
    else
        salirRango = true;
    end
end

disp('Sentimos no haber encontrado la mochila :(');