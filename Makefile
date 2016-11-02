project : main.o
	cc main.o -lncurses -lmenu -o project
main : main.c
	cc -c main.c
clean : 
	rm *.o 
