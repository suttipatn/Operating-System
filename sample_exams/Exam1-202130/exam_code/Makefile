all: beezy repair_demon say_hello
beezy: beezy.o say_hello.o
	gcc beezy.o say_hello.o -o beezy

beezy.o: beezy.c say_hello.h
	gcc -c beezy.c -o beezy.o

repair_demon: repair_demon.o
	gcc repair_demon.o -o repair_demon

repair_demon.o: repair_demon.c
	gcc -c repair_demon.c -o repair_demon.o

say_hello: say_hello.o
	gcc say_hello.o -o say_hello

say_hello.o: say_hello.c say_hello.c
	gcc -c say_hello.c -o say_hello.o

clean:
	rm -rf *.o repair_demon beezy *.dSYM
