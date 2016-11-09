function generador = genera(g, p)
generador = g;
tic
if (g>= 1 && g<= p-1) || length(factor(p)) ~= 1
    q = p-1;
    F = factor(q);
    for i=1:length(F)
        aux = uint64(potencia(generador, q/F(i), p));
        if aux == 1
            generador = 0;
            break;
        end
    end
    toc
else
   generador = 0;
   toc
   return; 
end
