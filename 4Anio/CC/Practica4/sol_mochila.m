function [v, valida] = sol_mochila(s, obj)

if mochila(s)==1
    valida = 1;
else
    valida = 0;
end

%Ordenamos el vector, en caso de que no este ordenador
n = length(s);
v = zeros(1,n);

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
    