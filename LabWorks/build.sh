#!/bin/bash

if [[ -n "$1" ]]
	then
		if [[ $1 == "dir" ]]
			then
			mkdir build
			cd build
			cmake ..
			make
		fi
		if [[ $1 == "run" ]]
			then
			./build/main/prog
		fi
		if [[ $1 == "rm" ]]
			then
			rm -rf build
		fi
		
	else 
		echo "Запуск программы:"
        echo "  ./build [Опции]"
        echo "Опции:"
        echo "  dir — собрать программу в ./build"
        echo "  run — запустить программу ./main/main.cpp"
        echo "  rm —  удалить сборку программы"

fi	  
