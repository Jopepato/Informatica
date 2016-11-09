function generador = genera_0(g,p)
generador = g;
tic
if (g>= 1 && g<= p-1) || length(factor(p)) ~= 1
    B =[];
    for i=1:p-1
        b = uint64(potencia(g, i, p));
        if find(B == b)
            %Se sale porque esta repe
            generador = 0;
            toc
            return;
        else
            B = [B, b];
        end
    end
    toc
else
   generador = 0;
   toc
   return; 
end