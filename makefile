all:
	gcc -o test main.c list.c
	./test
clean:
	rm test
