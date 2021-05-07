#!/bin/bash

if !(test -d "./images"); then
  echo "images directory not found"
else

  if !(test -d "./ALL"); then
    mkdir "./ALL"
  fi;

  num=1
  find ./images/PNEUMONIA | grep "IM" | while read f; do mv "$f" ./ALL/PNEUMONIA_$num.png; num=$((num+1)); done
  num=1
  find ./images/NORMAL | grep "IM" | while read f; do mv "$f" ./ALL/NORMAL_$num.png; num=$((num+1)); done

fi;
