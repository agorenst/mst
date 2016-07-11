kruskal: kruskal.cpp
	clang++ -std=c++11 -Wall kruskal.cpp -o kruskall

clean:
	rm -f *.o *~ kruskall
