all: prim kruskal
prim: prim.cpp
	clang++ -g -std=c++11 -Wall prim.cpp -o prim
kruskal: kruskal.cpp
	clang++ -std=c++11 -Wall kruskal.cpp -o kruskal

clean:
	rm -f *.o *~ kruskal prim
