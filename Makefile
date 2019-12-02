main: myshell.c twc.c
	gcc myshell.c -o myshell.o -pthread -lreadline
	gcc twc.c -o twc -fopenmp

.PHONY: clean
	clean:
		rm -rf *.o
