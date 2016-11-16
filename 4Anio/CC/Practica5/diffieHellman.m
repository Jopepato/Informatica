function diffieHellman(g, p)

if genera(g,p) ~= 0
    %Se podrá seguir con esta funcion
    
    %Generamos el random de A y B
    randA = randi([1 p-1]);
    fprintf('A genera el numero aleatorio randA: %d\n', randA);
    randB = randi([1 p-1]);
    fprintf('B genera el numero aletorio randB: %d\n\n', randB);
    
    %Ahora generamos las claves para A y B
    pote_a = potencia(g, randA, p);
    fprintf('A envia a B el producto: %d\n', pote_a);
    pote_b = potencia(g, randB, p);
    fprintf('B envia a A el producto: %d\n\n', pote_b);
    
    %Paso 3, A y B calculan la clave con la que van a cifrar los mensajes
    
    claveA = potencia(pote_b, randA, p);
    fprintf('A obtiene la clave: %d\n', claveA);
    claveB = potencia(pote_a, randB, p);
    fprintf('B obtiene la clave %d\n\n', claveB);
    
else
   %No se puede hacer cosas
   fprint('El g introducido y p no son validos puesto que no son generadores');
end