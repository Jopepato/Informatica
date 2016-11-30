function doble = letra2numeros(texto)

doble = [];
%Ahora metemos un 0 delante de cada digito

for i=1:length(texto)
    numero = num2str(letranumero(texto(i)));
    if length(numero) == 1
       aux = strcat('0', numero);
    else
       aux = numero;
    end
    doble = [doble, aux];
end