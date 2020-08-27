a.out: functions.o main.o
		gcc functions.c main.c
functions.o: functions.c
		gcc -c functions.c
main.o: main.c server.h
		gcc -c main.c
    