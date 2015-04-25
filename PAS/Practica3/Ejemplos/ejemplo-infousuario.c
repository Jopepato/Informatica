#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *lgn;
    struct passwd *pw;
    struct group *gr;

    if (argc < 2)
    {
        if ((lgn = getlogin()) == NULL || (pw = getpwnam(lgn)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
    }
    else
    {
        lgn = argv[1];

        if ((pw = getpwnam(lgn)) == NULL)
        {
            fprintf(stderr, "Get of user information failed.\n");
            exit(1);
        }
    }

    printf("Nombre: %s\n", pw->pw_gecos);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Número de grupo principal: %d\n", pw->pw_gid);

    // Obtenemos el nombre del grupo a tavés del número
    gr = getgrgid(pw->pw_gid);

    printf("Nombre del grupo principal: %s\n", gr->gr_name);

    exit(0);

}

