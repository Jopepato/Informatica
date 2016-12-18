function blo = prepabloque(na, nb,  bloque)
texto='';
aux_tex='';
%Funcion auxiliar para preparar los bloques de auten_firma
%Esta funcion es similar a num_descifra
for i = 1:length(bloque)
   auxt=num2str(bloque(i));
   while(length(auxt) < (length(num2str(na))-1))
      auxt=strcat('0',auxt); 
   end
   texto=strcat(texto,auxt);
end
if mod(length(texto),2)==1
   texto=texto(1:length(texto)-1);
end
texto=reshape(texto,2,[]);
texto=texto';
[row, col]=size(texto);
for i = row:-1:1
    if(strcmp(texto(i,:), '30'))
        texto=texto(1:length(texto)-1, :);
    else
        break
    end
end
[row, cols]=size(texto);
for i = 1:row
    aux_tex=strcat(aux_tex,texto(i,:));
end
tama=length(num2str(nb));
blo=prepa_num_cifrar(tama,aux_tex);
