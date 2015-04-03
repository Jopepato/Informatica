#!/bin/bash

#Suponemos que ya tenemos la web descargada con el wget

#Ahora procedemos a formatear el texto

echo -e "Descargando la web...\n"

#Descargamos la pagina web de los tuits
wget https://twitter.com/GeoPortalMityc &> descarga.tmp


echo -e "\nMostramos los tuits\n\n"

cat GeoPortalMityc | grep -E -o "EcoPrecio.*<" | sed -n -r 's/([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ](.*es)[ ](.*en)[ ](.*<)/Precio: "\5" Ciudad: "\4" Combustible: "\2 \3" Direccion: "\6" /p' | sed -r -e 's/ es//' | sed -r -e 's/ en//' | sed -r -e 's/<//' | sort 


#Y borramos el archivo para la proxima vez que lo ejecutemos lo volvamos a descargar
rm GeoPortalMityc
rm descarga.tmp