output : main.o project.o 
	gcc main.o project.o -o output

main.o : main.c 
	gcc -c main.c

project.o : project.c project.h
	gcc -c project.c

clean:
	rm -rf *.o
