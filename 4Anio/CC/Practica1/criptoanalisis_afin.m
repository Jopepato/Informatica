function criptoanalisis_afin(v, m)
format shortg
[frecuencia, freordenada] = cripto_ana_orden(v);
abecedario = 'abcdefghijklmnñopqrstuvwxyz';
%Ahora tenemos las frecuencias de dicha criptografia
frecCast = [0.1311 4; 0.106 0; 0.0847 19; 0.0823 15; 0.0716 8; 0.0714 13; 0.0695 18; 0.0587 3; 0.054 20; 0.0485 2; 0.0442 11; 0.0434 21; 0.0311 12; 0.0271 16; 0.014 6; 0.0116 1; 0.0113 5; 0.0082 22; 0.0079 25; 0.0074 17; 0.006 7; 0.0026 26; 0.0025 9; 0.0015 24; 0.0012 23; 0.0011 10; 0.001 14];

a = 0;

    for i=1:length(v)-1
        
        %Cogemos las 2 letras mas utilizadas tanto del alfabeto castellano
        %como de la frase introducida y las relacionamos con un sistema de
        %ecuaciones para despejar la clave y d
        x1 = round(frecCast(i,2));
        x2 = round(frecCast(i+1, 2));
        y1 = round(freordenada(i,2));
        y2 = round(freordenada(i+1,2));
        B = [x1 1;x2 1];
        C = [y1; y2];
        B = inv_modulo(B, length(abecedario));
        A = B*C;
        %Ahora resolvemos el sistema de ecuaciones para obtener k y d y
        %desciframos con afin
        clave = mod(A(1,1), length(abecedario))
        d = mod(A(2,1), length(abecedario))
        %Una vez tenemos la clave y d, se las pasamos al descifrado afin
        %para que intente descifrar
        descifradoafin = desafin(clave, d, v)
        prompt = 'Si quieres probar otra clave introduce 1, en caso contrario introduce 0 ->';
        a = input(prompt);
        if a == 0
            break
        end
    end
