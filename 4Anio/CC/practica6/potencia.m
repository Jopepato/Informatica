function pote = potencia(c, d, n)

%Pasamos el modulo de decimal a binario
exponente = dec2bin(d);

valoresExponente =[];
baseModulo = uint64(mod(c, n));
aux = uint64(baseModulo);
pote = 1;
for i=length(exponente):-1:1
   if exponente(i) == '1'
      pote = uint64(mod(pote*aux, n));
   end
   aux = uint64(mod(aux*aux, n));
end




