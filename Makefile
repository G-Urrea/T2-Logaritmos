flags:=-c -flto -Wall

test2: heap.o graph.o alg2.o test2.o
	gcc -flto -ggdb -O2 -o test2 heap.o graph.o alg2.o test2.o

heap.o: heap.c
	gcc ${flags} heap.c

fibo.o: fibo.c
	gcc ${flags} fibo.c

graph.o: graph.c
	gcc ${flags} graph.c

alg2.o: alg2.c
	gcc ${flags} alg2.c

alg3.o: alg3.c
	gcc ${flags} alg3.c

test2.o: test2.c
	gcc ${flags} test2.c

clean:
	rm -f *.o