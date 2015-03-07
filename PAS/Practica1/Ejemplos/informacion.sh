#!/bin/bash
STR="Bienvenido $USER, tu identificador es $UID.\nEsta es la shell numero $SHLVL, que lleva $SECONDS arrancada.\nLa arquitectura de esta maquina es $MACHTYPE y el cliente de  terminal es $TERM"
echo -e $STR
