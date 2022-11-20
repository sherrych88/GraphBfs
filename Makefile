all: graph

graph: graph.c
	gcc -Wall -Werror graph.c -o graph

clean:
	rm -rf graph