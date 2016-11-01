function factores_c = factorescomunes(w, s1)

%Comprobamos si w tiene factores comunes con s1
f = factor(w);
for i=1:length(f)
    %Comprobamos cada factor
    for j=1:length(s1)
       f1 = factor(s1(j));
       for k=1:length(f1)
           if(f(i) == f1(k))
               factores_c = 1;
               return
           end
       end
    end
end

factores_c = 0;