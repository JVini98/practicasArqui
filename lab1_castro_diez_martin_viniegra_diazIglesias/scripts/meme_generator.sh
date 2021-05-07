#!/bin/bash

if test -z $1;
then
  read -p "Introduzca el nombre del meme: " nombre
else
  nombre=$1
fi;

if test -z $2;
then
  read -p "Introduzca la frase de arriba: " arriba
else
  arriba=$2
fi;

if test -z $3;
then
  read -p "Introduzca la frase de abajo: " abajo
else
  abajo=$3
fi;

nombre=$(echo "$nombre" | tr A-Z a-z)
arriba=$(echo "$arriba" | tr A-Z a-z)
abajo=$(echo "$abajo" | tr A-Z a-z)

nombre=$(echo "$nombre" | tr " " _)
arriba=$(echo "$arriba" | tr " " _)
abajo=$(echo "$abajo" | tr " " _)

open "https://memegen.link/$nombre/$arriba/$abajo.jpg"
echo "Downloading your meme"
wget "https://memegen.link/$nombre/$arriba/$abajo.jpg"
