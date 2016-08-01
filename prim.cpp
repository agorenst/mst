#include <list>
#include <map>
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>
#include <array>

// Trying to get a very "explicit" implementation of Prim's.
// This... doesn't really work. Need to revisit it at some point.

using namespace std;

struct edge {
    int u = -1;
    int v = -1;
    double w = -1;
    public:
    edge() {}
    edge(int u, int v, double w): u(u), v(v), w(w) {}
};


const double infinity = numeric_limits<double>::max();


int delete_min(list<int>& priority_queue, const vector<double>& costs) {
    auto min_elt_ptr = min_element(begin(priority_queue), end(priority_queue),
                         [&](int x, int y) { return costs[x] < costs[y]; });

    //int result = distance(begin(priority_queue), min_elt_ptr);
    if (min_elt_ptr == end(priority_queue)) { return 0; }
    priority_queue.erase(min_elt_ptr);
    int result = *min_elt_ptr;
    //cout << "result1: " << result1 << " result2: " << result2 << endl;
    //*min_elt_ptr = infinity;
    return result;
}

void decrease_key(list<int>& priority_queue, const vector<int>& costs, int v) {
    // priority queue is the cost vector right now.
}

class weighted_undirected_graph {
    private:
        vector<list<int>> edges;
        map<pair<int,int>, double> weights;
    public:
        weighted_undirected_graph(const int nodecount, const int edgecount):
            edges(nodecount) {}
        void add_edge(int u, int v, double w) {
            if (u > v) { swap(u,v); }
            weights[make_pair(u,v)] = w;
            // check for multi-edges?
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        double edge_weight(int u, int v) const {
            if (u > v) { swap(u,v); }
            return weights.find(make_pair(u,v))->second;
        }

        const list<int>& neighbors(int u) {
            return edges[u];
        }
        void remove_node(int u) {
            //cout << "Removing node: " << u << endl;
            edges[u].clear();
            //for (int i = 0; i < edges.size(); ++i) {
            for (auto& v : edges) {
                auto it = find(begin(v), end(v), u);
                if (it != end(v)) {
                    v.erase(it);
                }
            }
        };
};

// assuming nodes are {1,n}, and it's a connected undirected graph.
int main(int argc, char* argv[]) {
    int node_count, edge_count;
    cin >> node_count;
    ++node_count;
    cin >> edge_count;

    weighted_undirected_graph g(node_count,edge_count);

    for (int i = 0; i < edge_count; ++i) {
        int u, v;
        double w;
        cin >> u;
        cin >> v;
        cin >> w;

        g.add_edge(u,v,w);
    }

    vector<double> costs(node_count,infinity);
    costs[1] = 0;
    auto cost_comparer = [&costs](int x, int y) { return costs[x] > costs[y]; };

    vector<int> pq(node_count);

    // lots of gnarly off-by-one errors potentially here, but the test cases seem OK.
    for (int i = 0; i < node_count; ++i) { pq[i] = i+1; }
    pq.pop_back();
    // oh goodness we don't need a map, but there's all these off-by-one if the
    // input graph has 0 or 1 as the smallest node index.
    map<int,int> prev;

    make_heap(begin(pq), end(pq), cost_comparer);


    // the current "stop" condition is a hack about how min_element works when
    // all the elements
    while (pq.size()) {
        auto min_node = pq[0];
        pop_heap(begin(pq), end(pq), cost_comparer);
        pq.pop_back();

        for (auto&& v : g.neighbors(min_node)) {
            if (costs[v] > g.edge_weight(min_node,v)) {
                costs[v] = g.edge_weight(min_node,v);
                prev[v] = min_node;
                // decrease key here
            }
        }
        // can we be smarter about maintaining the priority queue?
        make_heap(begin(pq), end(pq), cost_comparer);

        // this doesn't remove the edge *weights* (weirdly),
        // so we can reconstitute the graph easily
        g.remove_node(min_node);
    }

    for (auto& p : prev) {
        cout << p.first << " "
             << p.second << " "
             << g.edge_weight(p.first,p.second) << endl;
    }

    double weight = 0;

    for (auto& p : prev) {
        auto u = p.first;
        auto v = prev[u];
        weight += g.edge_weight(u,v);
    }
    cout << weight << endl;
}
