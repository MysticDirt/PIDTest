pid.out: main.o pid.o
	gcc -g -Wall -Werror -o pid.out main.o pid.o

main.o: main.c
	gcc -g -Wall -Werror -c main.c

pid.o: pid.c pid.h
	gcc -g -Wall -Werror -c pid.c

clean:
	rm -rf *.o *.out