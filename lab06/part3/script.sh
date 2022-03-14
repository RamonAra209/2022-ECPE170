#!/bin/bash

declare -a values=(256 512 768 1024 1280 1536 1792 2048)
echo "size, algorithm1, algorithm2" > output.txt

for ((i = 0; i<8; i++)) 
do
	size=${values[i]}  
	output=$(./matrix_math 1 ${values[i]} )
	string1=$(echo $output | awk '{print $NF}')
	output=$(./matrix_math 1 ${values[i]} )
	string2=$(echo $output | awk '{print $NF}')
	echo ${size}, ${string1}, ${string2} >> output.txt
done
