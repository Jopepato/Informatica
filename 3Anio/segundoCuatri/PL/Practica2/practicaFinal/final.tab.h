/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_FINAL_TAB_H_INCLUDED
# define YY_YY_FINAL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    VAR = 259,
    CONSTANTE = 260,
    FUNCION0_PREDEFINIDA = 261,
    FUNCION1_PREDEFINIDA = 262,
    FUNCION2_PREDEFINIDA = 263,
    INDEFINIDA = 264,
    PRINT = 265,
    WHILE = 266,
    IF = 267,
    ELSE = 268,
    READ = 269,
    _LUGAR = 270,
    CADENA = 271,
    READ_CADENA = 272,
    PRINT_CADENA = 273,
    HACER = 274,
    FIN_MIENTRAS = 275,
    FIN_SI = 276,
    REPETIR = 277,
    HASTA = 278,
    ENTONCES = 279,
    PARA = 280,
    PASO = 281,
    FIN_PARA = 282,
    DESDE = 283,
    _BORRAR = 284,
    ASIGNACION = 285,
    O_LOGICO = 286,
    Y_LOGICO = 287,
    MAYOR_QUE = 288,
    MENOR_QUE = 289,
    MENOR_IGUAL = 290,
    MAYOR_IGUAL = 291,
    DISTINTO = 292,
    IGUAL = 293,
    DIV_ENTERA = 294,
    POTENCIA = 295,
    MODULO = 296,
    CONCATENACION = 297,
    UNARIO = 298,
    NEGACION = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 26 "final.y" /* yacc.c:1909  */
             
       Symbol *sym;    /* puntero a la tabla de simbolos */
       Inst *inst;     /* instruccion de maquina */

#line 104 "final.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FINAL_TAB_H_INCLUDED  */
