function [cp, mu, invw] = mochila_mh(s1)
%Primero comprobamos si la mochila es valida
if mochila(s1)
   %Ahora toca escoger mu, que se lo pedimos al usuario
   prompt = 'Introduce el valor de mu: ';
   salir = false;
   while (salir==false)
        mu = input(prompt);
        if mu<(2*s1(length(s1))+2)
            disp('El valor de mu introducido no es válido');
        else
            salir = true;
        end
   end
   salir = false;
   i = 2;
   while salir==false
       if gcd(mu, i) == 1
          %Ahora comprobamos que no tenga  factores comunes con la mochila
          if factorescomunes(i, s1) == 0
            w = i;
            salir = true;
          end
       end
       i = i+1;
   end
    %Ahora hallamos la inversa de w en mu
    [G, U, invw] = gcd(mu, w);
    %Y calculamos la mochila
    w
    cp = [];
    for i=1:length(s1)
        cp = [cp, mod(s1(i)*w, mu)];
    end
end