/*
Ejemplo extraído del estándar POSIX y glibc.
Enlace a la página de documentación de la implemencación de getopt de glibc:
http://pubs.opengroup.org/onlinepubs/9699919799/functions/getopt.html
http://www.gnu.org/software/libc/manual/html_node/Getopt.html
http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
*/

#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    /* Las variables optind, optarg y optopt las declara y actualiza
       implíticamente getopt()
    */

    opterr = 0;

    /* ':' indica que 'c' tiene un argumento
       "abc:" -> busca como opciones a y b sin argumentos y c con un argumento
                 obligatorio.*/
    /* getopt devuelve -1 si ya hemos consultado toda la línea de argumentos.
       Sino, devuelve el caracter de opción encontrado (para caracteres válidos).
             devuelve ? si el caracter no es válido según la cadena especificada.*/
    while ((c = getopt (argc, argv, "abc:")) != -1)
    {
        /* Podemos observar qué pasas con las variables externas que va gestionando
           getopt() durante las sucesivas llamadas 
           optopt recoge el valor de la opción cuando es desconocida (?)*/
        printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);
        switch (c)
        {
        case 'a':
            aflag = 1;
            break;
        case 'b':
            bflag = 1;
            break;
        case 'c':
            cvalue = optarg;
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "La opción %c requiere un argumento.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Opción desconocida '-%c'.\n", optopt);
            else
                fprintf (stderr, "Caracter `\\x%x'.\n", optopt);
            return 1;
        default:
            abort ();
        }
    }



    printf ("aflag = %d, bflag = %d, cvalue = %s\n",
            aflag, bflag, cvalue);

    /* Esta último bucle controla opciones introducidas por el usuario
       que no hayan sido procesadas. Compara el número de argumentos recibidos
       con el número de opciones reconocidas. Como getopt() internamente
       reordena los valores de argv, las primeras posiciones de argv corresponden
       a opciones conocidas y las últimas, a partir de optind, a opciones no
       reconocidas */
    for (index = optind; index < argc; index++)
        printf ("Argumento de la línea de comandos que NO es una opción %s\n", argv[index]);

    // El siguiente condicional permitiría dar un valor por defecto a la opción c
    if(cvalue==NULL)
        cvalue="ValorPorDefecto";
    return 0;
}


