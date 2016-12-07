function [amplio, texto_bit] = textobit_col(texto, col)

numeros = uint8(texto)
bits = dec2bin(numeros, 8);
bits = reshape(bits', 1, []);
texto_bit =[];
x=1;
amplio = 0;
while 1
    for i=1:col
        if x<=length(bits)
            texto_bit = [texto_bit, bits(x)];
        else
            texto_bit = [texto_bit, '0'];
            amplio = amplio +1;
        end
        x = x+1;
    end
    if x>length(bits)
       break; 
    end
end

texto_bit = reshape(texto_bit, col, [])';