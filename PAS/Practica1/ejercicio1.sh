#!/bin/bash
if [ ! $# -eq 1 ];
then
  echo "Numero de parametros introducidos incorrectos"
fi

if [ -d $1]
then
  if [ -d $2]
  then
    tar -czfv "$2.tar.gz" "$1"
  else
    tar -czfv "$1.tar.gz" "$1"
  fi
fi
