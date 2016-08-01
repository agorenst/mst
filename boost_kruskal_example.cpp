// This code is based off of http://www.boost.org/doc/libs/1_61_0/libs/graph/example/kruskal-example.cpp,
// and not knowing a darn thing about licenses I'm including there's below. I'm including this just
// for "correctness checking" -- I'm assuming the boost implementation of Kruskal's algorithm is *correct*.
//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee, 
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>
#include <fstream>

using namespace std;

int
main()
{
  using namespace boost;
  typedef adjacency_list < vecS, vecS, undirectedS,
    no_property, property < edge_weight_t, double > > Graph;
  typedef graph_traits < Graph >::edge_descriptor Edge;
  typedef graph_traits < Graph >::vertex_descriptor Vertex;
  typedef std::pair<int, int> E;

  int num_nodes;
  int num_edges;
  cin >> num_nodes;
  cin >> num_edges;
  E* edge_array = new E[num_edges];
  double* weights = new double[num_edges];
  for (int i = 0; i < num_edges; ++i) {
      int u, v;
      double w;
      cin >> u;
      cin >> v;
      cin >> w;
      edge_array[i] = E(u,v);
      weights[i] = w;
  }

  Graph g(edge_array, edge_array + num_edges, weights, num_nodes);
  property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
  std::vector < Edge > spanning_tree;

  kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

  double treeWeight = 0;
  std::cout << "Print the edges in the MST:" << std::endl;
  for (std::vector < Edge >::iterator ei = spanning_tree.begin();
       ei != spanning_tree.end(); ++ei) {
    std::cout << source(*ei, g) << " " << target(*ei, g)
      << " " << weight[*ei]
      << std::endl;
      treeWeight += weight[*ei];
  }
  cout << treeWeight << endl;
  return EXIT_SUCCESS;
}
