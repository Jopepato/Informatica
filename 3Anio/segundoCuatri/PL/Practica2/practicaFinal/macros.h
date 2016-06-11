#ifndef MACROS_H
#define MACROS_H

#define LUGAR(x,y)   printf("\033[%d;%dH",x,y)
#define BORRAR       printf("\33[2J") 
#define PARPADEO     printf("%c[5m",27)
#define APAGA        printf("%c[0m",27)
#define INVERSO      printf("%c[7m",27)
#define SUBRAYADO    printf("%c[4m",27)
#define INTENSIDAD   printf("%c[1m",27)

#define GREEN   printf("\e[32m")
#define RED     printf("\e[31m")
#define YELLOW  printf("\e[33m")
#define BLUE    printf("\e[34m")
#define WHITE   printf("\e[37m")
#define MAGENTA printf("\e[35m")
#define BLACK   printf("\e[30m")

#define ONGREEN   printf("\e[42m")
#define ONRED     printf("\e[41m")
#define ONYELLOW  printf("\e[43m")
#define ONBLUE    printf("\e[44m")
#define ONWHITE   printf("\e[47m")
#define ONMAGENTA printf("\e[45m") 
#define ONBLACK   printf("\e[40m")


#endif