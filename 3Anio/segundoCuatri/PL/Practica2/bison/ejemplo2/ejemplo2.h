#ifndef EJEMPLO2_H
#define EJEMPLO2_H

#define YYSTYPE double  /*  tipos de datos de la pila de yacc */

int yylex();

void yyerror(char *s);

void warning(char *s, char *t);

#endif
