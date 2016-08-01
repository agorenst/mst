#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

// A self-contained implementation of Kruskal's MST algorithm
// as described by http://highered.mheducation.com/sites/0073523402/index.html.
// I believe it is correct, at least on some initial test input, but hopefully
// I will soon be able to provide a more comprehensive test suite for
// correctness and (asymptotic) performance.

struct edge {
    int u = -1;
    int v = -1;
    int w = -1;
    public:
    edge() {}
    edge(int u, int v, int w): u(u), v(v), w(w) {}
};


ostream& operator<<(ostream& o, const edge& e) {
    o << "(" << e.u << " " << e.v << " " << e.w << ")";
    return o;
}

// We assume the set upon which we build the disjoint
// unions is [0,n).
// This is where a lot of interesting work happens to
// make the runtime fast.
class disjoint_unions {
    private:
    struct set_type {
        int p, r;
    };
    vector<set_type> data;
    public:
    disjoint_unions(int n): data(n) {
        for (int i = 0; i < n; ++i) {
            data[i] = {i,0};
        }
    }

    int union_find(int x) {
        if (data[x].p != x) {
            data[x].p = union_find(data[x].p);
        }
        return data[x].p;
    }

    void make_union(int x, int y) {
        auto xp = data[x].p;
        auto yp = data[y].p;
        if (yp == xp) { return; }
        
        if (data[xp].r < data[yp].r) {
            data[xp].p = yp;
        }
        else if (data[xp].r > data[yp].r) {
            data[yp].p = xp;
        }
        else {
            data[yp].p = xp;
            data[xp].r++;
        }
    }
};

// comparator object
auto edge_weight_sorter = [](const edge e1, const edge e2) { return e1.w < e2.w; };

int main(int argc, char* argv[]) {
    int node_count, edge_count;

    //////////////////////////////////////////////////////////////
    // Read in the input and initialize the disjoint
    // union structure.
    //////////////////////////////////////////////////////////////
    cin >> node_count;
    cin >> edge_count;

    vector<edge> edges(edge_count);

    // initialize the union_find parents.
    disjoint_unions unions(node_count+1);

    for (int i = 0; i < edge_count; ++i) {
        int u, v, w;
        cin >> u;
        cin >> v;
        cin >> w;
        edge e = {u,v,w};
        edges[i] = e;
    }

    // Initialize the container to hold the MST:
    // largest possible size--right? if graph not connect then only shrinks MST.
    vector<edge> MST(node_count+1); 


    // This is the actual algorithm! It is so small, as we've already
    // defined all the helping structures.
    //// We start by sorting the edges by "priority":
    sort(begin(edges), end(edges), edge_weight_sorter);
    int s = 0;
    for (auto&& e : edges) {
        // If an edge is characterized by a different set, we
        // can add them without adding cycles.
        if (unions.union_find(e.u) != unions.union_find(e.v)) {
            MST[s++] = e;
            unions.make_union(e.u, e.v);
        }
    }
    // That's the whole algorithm! Now we output the result.

    cout << "MST" << endl;
    for (int i = 0; i < s; ++i) {
        cout << MST[i] << endl;
    }
    int total_weight = 0;
    for (int i = 0; i < s; ++i) {
        total_weight += MST[i].w;
    }
    cout << "Total weight: " << total_weight << endl;
}
