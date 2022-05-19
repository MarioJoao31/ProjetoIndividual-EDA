all:clean 
	gcc main.c funcoes.c -o main
	./main
clean:
	rm -rf main