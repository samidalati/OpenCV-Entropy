#!/bin/sh

for file; do
  base=${file%.*}
  case $file in 
    *.c)
      echo "Compiling $base"
      gcc -ggdb $(pkg-config --cflags --libs opencv) -o "$base" "$file" `pkg-config --libs opencv`
      ;;
    *.cpp)
      echo "Compiling $base"
      g++ -ggdb `pkg-config --cflags opencv` -o "$base" "$file" `pkg-config --libs opencv`
      ;;
    *)
      echo "Don't know what to do with $file"
      ;;
  esac
done

