function mat_p = matper(p)

%Primero comprobamos que p es una permutación
if permutacion_v(p) == 1
    %Es una permutación
    mat_p = zeros(length(p), length(p));
    
    %Ahora ponemos 1 en las posiciones que estan en la permutacion
    for i=1:length(p)
       mat_p(i, p(i)) = 1; 
    end
else
   error('ErrorTests:convertTest','El vector introducido no es una permutación')
end