function intrusodiffieHellman(g, p)

if genera(g,p) ~= 0
    %Se podrá seguir con esta funcion
    
    %Generamos el random de A
    randA = randi([1 p-1]);
    fprintf('A genera el numero aleatorio randA: %d\n', randA);
    
    %A envia la potencia a B
    pote_a = potencia(g, randA, p);
    fprintf('A envia a B el producto: %d\n\n', pote_a);
    
    %Añadimos lo del intruso
    
    fprintf('EL INTRUSO CAPTURA pote_a: %d, y lo guarda\n', pote_a);
    randC = randi([1 p-1]);
    fprintf('EL INTRUSO GENERA cc: %d\n', randC);
    pote_c = potencia(g, randC, p);
    fprintf('EL INTRUSO ENVIA a B: %d\n', pote_c);
    fprintf('B piensa que le llega A\n\n');
    
    %Ahora generamos los de B
    randB = randi([1 p-1]);
    fprintf('B genera un número aleatorio %d', randB);
    pote_b = potencia(g, randB, p);
    fprintf('B envia a A : %d', pote_b);
    
    %El intruso captura lo que envia B y le envia a A pote_c
    fprintf('EL INTRUSO CAPTURA pote_b: %d y lo guarda\n', pote_b);
    fprintf('EL INTRUSO ENVIA a A el mismo dato que le ha enviado a B: %d\n', pote_c);
    fprintf('A piensa que le llega de B\n\n');
    
    %A y B calculan las claves con los datos que le ha enviado el intruso
    claveA = potencia(pote_c, randA, p);
    claveB = potencia(pote_c, randB, p);
    
    fprintf('A y B calculan sus claves con los datos que les llegan\n');
    fprintf('A cifrará con clave: %d\n', claveA);
    fprintf('B cifrará con clave: %d\n\n', claveB);
    
    fprintf('C también sabe sus claves secretas asi que su labor se da por cumplida\n\n');
    
else
   %No se puede hacer cosas
   fprint('El g introducido y p no son validos puesto que no son generadores');
end