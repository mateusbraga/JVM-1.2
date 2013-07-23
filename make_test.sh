#!/bin/sh

javac -source 1.2 -target 1.2 *.java

for file in *.class
do
    name=$(basename "$file" .class)
    echo --------------------------------------
    echo ${name}
    make
    ./jvm $name > output.txt

    java $name > certo.txt

    echo ${name}
    diff certo.txt output.txt
    read -p "Press [Enter] to next file"
done
