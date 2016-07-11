#include <list>
#include <map>
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>
#include <array>

struct edge {
    int u = -1;
    int v = -1;
    int w = -1;
    public:
    edge() {}
    edge(int u, int v, int w): u(u), v(v), w(w) {}
};

using namespace std;

const int infinity = numeric_limits<int>::max();

int delete_min(list<int>& priority_queue, const vector<int>& costs) {
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
        const int firstnode = 0;
        vector<list<int>> edges;
        map<pair<int,int>, int> weights;
    public:
        weighted_undirected_graph(const int firstnode, const int nodecount, const int edgecount):
            firstnode(firstnode), edges(nodecount+firstnode) {

        }
        void add_edge(int u, int v, int w) {
            if (u > v) { swap(u,v); }
            weights[make_pair(u,v)] = w;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        int edge_weight(int u, int v) const {
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

    weighted_undirected_graph g(1,node_count,edge_count);

    for (int i = 0; i < edge_count; ++i) {
        int u, v, w;
        cin >> u;
        cin >> v;
        cin >> w;

        g.add_edge(u,v,w);
    }

    vector<int> costs(node_count,infinity);
    list<int> priority_queue;
    for (int i = 1; i < node_count; ++i) { priority_queue.push_back(i); }
    vector<int> prev(node_count,-1);

    costs[1] = 0;


    // the current "stop" condition is a hack about how min_element works when
    // all the elements
    for (int min_node = delete_min(priority_queue, costs);
             min_node != 0;
             min_node = delete_min(priority_queue, costs)) {
        //cout << "min node: " << min_node << endl;
        for (auto&& v : g.neighbors(min_node)) {
            //cout << "\tneighbor: " << v << endl;
            if (costs[v] > g.edge_weight(min_node,v)) {
                costs[v] = g.edge_weight(min_node,v);
                prev[v] = min_node;
                decrease_key(priority_queue,costs,v);
            }
        }
        g.remove_node(min_node);
    }
    for (int i = 2; i < prev.size(); ++i) {
        auto u = i;
        auto v = prev[i];
        cout << u << " " << v << " ";
        cout << g.edge_weight(u,v) << endl;
    }

    int weight = 0;

    for (int i = 2; i < prev.size(); ++i) {
        auto u = i;
        auto v = prev[i];
        weight += g.edge_weight(u,v);
    }
    cout << weight << endl;
}
