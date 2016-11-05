function [v, valida] = sol_mochila(s, obj)
%Funcion que obtiene un objetivo a partir de una mochila cualquiera, ya sea
%supercreciente o no

%Comprobamos si es valida para el segundo parametro
if mochila(s)==1
    valida = 1;
else
    valida = 0;
end

n = length(s);
v = zeros(1,n);
%Hacemos un vector de ceros para despues poner 1 en las casillas de los
%objetos de la mochila que hemos cogido
for i=n:-1:1
    if s(i)<=obj
        %Cogemos ese objeto
        v(i) = 1;
        obj = obj - s(i);
    end
end
if obj~=0
    %Si no hemos alcanzado el objetivo
    v = 0;
    disp('Con el algoritmo usado no encuentro objetivo\n')
end
    