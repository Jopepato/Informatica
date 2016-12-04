function blo = prepabloque(na, nb,  bloque)
aux = [];

for i=1:length(bloque)
    auxt = num2str(bloque(i));
    while length(auxt) < length(num2str(nb))-1
       auxt = strcat('0', auxt); 
    end
    aux = strcat(aux, auxt);
end
aux
var = '';
blo = [];
for i=1:length(aux)
   %Vamos a ir metiendo de length de na y asi lo formamos
   var = strcat(var, aux(i));
   if length(var) == length(num2str(na))
      blo = [blo, str2num(var)];
      var = '';
   end
end
blo
