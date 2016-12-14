function n = pote(A,m)

%Comprobamos si la matriz es de 2x2
[filasA, columA] = size(A);
if filasA == 2 && columA == 2
    I = [1 0;0 1];
    n = 2;
    auxA = A;
    while 1
        auxA = mod(auxA*A, m);
        if auxA == I
            break;
        end
        n = n+1;
    end
else
   disp('La matriz A introducida no es de 2x2'); 
end