#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *lang = "LANG";
    const char *home = "HOME";

    char *value;

    value = getenv(lang);

    if (strstr(value,"ES"))
    {
        printf("\nLa carpeta del usuario/a es: %s\n", getenv(home));
    }
    else
    {
        printf("\nUser's home folder is: %s\n", getenv(home));
    }

    exit(0);
}
