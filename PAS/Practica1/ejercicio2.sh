#!/bin/bash
function html()
{
  echo "<ul>" >> "$1.html"
  for x in $(find $2 -maxdepth 1)
  do

      if [ $x != $2 ]

        then
          if [ -d $x ]

            then
              echo "<strong><li>$x</li></strong>" >> "$1.html"

              html $1 $x

              echo "</ul>" >> "$1.html"
            else
                echo "<li>$x</li>" >> "$1.html"
              fi
            fi
  done
}
if [ ! $# -eq 1 ]
	then
		echo "Numero de parametros introducidos incorrectos"

	else
		if [ -d $1 ]
		then
			echo "<html>" >> "$1.html"
      echo "<head><title>Ejercicio2_PAS</title></head>" >> "$1.html"
      echo "<body>" >> "$1.html"
      echo "<h1>Ejercico2_PAS</h1>" >> "$1.html"


      #Recorremos las carpetas y vamos listando los archivos

      html $1 $1

      #Y cerramos el html
      echo "</body></html>" >> "$1.html"

    else
      echo "El directorio especificado no existe"

    fi
fi
