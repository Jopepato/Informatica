function aux = aux_funcion(na, entrada)
    %Funcion auxiliar para auten_firma, que completa con 0 los bloques
    aux = '';
    for i=1:length(entrada)
        var = num2str(entrada(i));
        aux2 = length(num2str(na));
        while(length(var) < aux2 )
            var = strcat('0', var);
        end
        aux = strcat(aux,var );
    end