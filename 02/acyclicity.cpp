#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int step( vector<pair<bool, vector<int>>> &adj, int n) {
  // std::cout<< "step into " << n + << "\n";
  if(adj[n].first) {return 1;}
  adj[n].first = true;
  for(int i = 0; i < adj[n].second.size(); ++i) {
    int r = step(adj, adj[n].second[i]);
    if(r == 1) { return 1;}
  }
   adj[n].first = false;
  return 0;
}

int acyclic( vector<pair<bool, vector<int>>> &adj) {
  for(int i = 0; i < adj.size(); ++i) {
    // if(adj[i].first) {continue;}
    int r = step(adj, i);
    if(r == 1) {return 1;}
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<pair<bool, vector<int>>> adj(n);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
