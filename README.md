# GraphBfs
A graph representation using Breadth First Search in C.
# How To Run
- clone git https://github.com/sherrych88/GraphBfs.git
- cd GraphBfs
- using makefile:
  - mingw32-make
  - ./graph graph1.txt query1.txt (Test with same number for graph and query: ./graph graph2.txt query2.txt, etc.)
- not using makefile:
  - gcc -Wall -Werror graph.c -o graph
  - ./graph graph1.txt query1.txt
 - check results txt files
 # How It's Made
 - C
 - I used the adjacency lists graph representation, maintained in lexicographical order.
 - I implemented the Breadth First Search algorithm to search for and output specific keys in the query, in the order of BFS processing.
 # Notes
 - Creating this program gave me a greater understanding of using graphs and search algorithms.
