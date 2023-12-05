app.exe: cmp.o input_matrix.o errors.o main.o multiply_matrix.o print.o read_matrix.o
	gcc -g -o app.exe cmp.o input_matrix.o errors.o multiply_matrix.o print.o read_matrix.o main.o 
cmp.o : cmp.c cmp.h
	gcc -std=c99 -Wall -Werror -pedantic -c cmp.c 
input_matrix.o: input_matrix.c input_matrix.h
	gcc -std=c99 -Wall -Werror -pedantic -c input_matrix.c 
errors.o: errors.c errors.h 
	gcc -std=c99 -Wall -Werror -pedantic -c errors.c 
multiply_matrix.o: multiply_matrix.c multiply_matrix.h
	gcc -std=c99 -Wall -Werror -pedantic -c multiply_matrix.c
print.o: print.c print.h
	gcc -std=c99 -Wall -Werror -pedantic -c print.c
read_matrix.o: read_matrix.c read_matrix.h
	gcc -std=c99 -Wall -Werror -pedantic -c read_matrix.c
main.o: main.c cmp.h input_matrix.h errors.h multiply_matrix.h print.h read_matrix.h
	gcc -std=c99 -Wall -Werror -pedantic -c main.c
clean:
	rm *.o *.exe
