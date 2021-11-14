CCFlags= -W

list: testList.o list.o
	gcc testList.o list.o -o list
testList.o: testList.c list.h
	gcc -c $(CCFlags) testList.c -o testList.o
list.o: list.c list.h
	gcc -c $(CCFlags) list.c -o list.o
clear:
	rm -f *.o prog