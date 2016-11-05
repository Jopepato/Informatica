function valida = mochila2(s)

%Esta es una funcion como mochila pero sin comentarios para que en la
%funcion de criptoanalisis no este todo el rato saliendo por pantalla los
%comentarios de la funcion mochila
n = length(s);

for i=1:n-1
   if mod(s(i), 1) == 0 &&  s(i)>0
       sumatorio = 0;
       for j=1:i
            sumatorio = sumatorio + s(j);
       end
       if s(i+1) < s(i)
           valida = 0;
           return
       end
       
       if sumatorio > s(i+1)
            valida = 0;
            return
       end
   else
       valida = 0;
       return
   end
end

valida = 1;