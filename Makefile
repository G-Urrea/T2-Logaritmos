flags:=-c -flto -Wall

test1: alg1.o graph.o test1.o
	gcc -flto -ggdb -O2 -o test1 graph.o alg1.o test1.o

test2: heap.o graph.o alg2.o test2.o
	gcc -flto -ggdb -O2 -o test2 heap.o graph.o alg2.o test2.o
	
test3: fibo.o graph.o alg3.o test3.o
	gcc -flto -ggdb -O2 -o test3 fibo.o graph.o alg3.o test3.o

benchmark: heap.o fibo.o graph.o alg1.o alg2.o alg3.o benchmark.o
	gcc -flto -ggdb -O2 -o benchmark heap.o fibo.o graph.o alg1.o alg2.o alg3.o benchmark.o -lm

benchmark.o: benchmark.c
	gcc ${flags} benchmark.c

heap.o: heap.c
	gcc ${flags} heap.c

fibo.o: fibo.c
	gcc ${flags} fibo.c

graph.o: graph.c
	gcc ${flags} graph.c

alg1.o: alg1.c
	gcc ${flags} alg1.c

alg2.o: alg2.c
	gcc ${flags} alg2.c

alg3.o: alg2.c
	gcc ${flags} alg3.c

test1.o: test1.c
	gcc ${flags} test1.c

test2.o: test2.c
	gcc ${flags} test2.c

test3.o: test3.c
	gcc ${flags} test3.c

clean:
	rm -f *.o