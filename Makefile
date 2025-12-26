default:
	gcc main.c graphics.c -o build/main

run:
	cd build && ./main
