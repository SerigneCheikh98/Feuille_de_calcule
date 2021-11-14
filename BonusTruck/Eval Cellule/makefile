CCFlags= -W

evalCell: testCell.o eval.o list.o stack.o
	gcc testCell.o eval.o list.o stack.o -o evalCell -lm
testCell.o: testCell.c eval.h
	gcc -c $(CCFlags) testCell.c -o testCell.o
eval.o: eval.c eval.h
	gcc -c $(CCFlags) eval.c -o eval.o
list.o: ../List/list.c ../List/list.h
	gcc -c $(CCFlags) ../List/list.c -o list.o
stack.o: ../Stack/stack.c ../Stack/stack.h
	gcc -c $(CCFlags) ../Stack/stack.c -o stack.o
clear:
	rm -f *.o prog