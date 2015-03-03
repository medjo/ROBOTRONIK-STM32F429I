#!/bin/bash

#Ce script parcourt tous les fichiers sources ( *.c et *.h) présents dans "../../STM32Cube_FW_F4_V1.3.0/" et à chaque fois qu'il y a un #include qui fait référence à un fichier dont le chemin d'accès est indiqué avec des backslashs (comme l'arborescence sur windows : "\") il remplace les backslashs par des slashs ( "/" )pour que l'arborescence soit compréhensible par un système UNIX

STM32Cube="../../STM32Cube_FW_F4_V1.3.0/"


echo Cette opération peut prendre quelques instants...
for file in $(find $STM32Cube -name "*.c" -o -name "*.h")
do
#fullfile=$(basename $file)
#filename=${fullfile%.*}
#echo "Traitement de $filename"
sed '/#include/s/\\/\//g' $file > $file.tmp && mv -f $file.tmp $file
done
echo 'Opération terminée !'
