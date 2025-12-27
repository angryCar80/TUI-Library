default:
	gcc main.c graphics.c button.c -o build/main

run:
	cd build && ./main
