all: prim kruskal boost_answer
boost_answer: boost_kruskal_example.cpp
	clang++ -O3 -std=c++11 -Wall boost_kruskal_example.cpp -o boost_answer
prim: prim.cpp
	clang++ -O3 -std=c++11 -Wall prim.cpp -o prim
kruskal: kruskal.cpp
	clang++ -O3 -std=c++11 -Wall kruskal.cpp -o kruskal

clean:
	rm -f *.o *~ kruskal prim boost_answer
