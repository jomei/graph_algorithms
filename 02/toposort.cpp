#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<pair<bool, vector<int>>>& adj, vector<int>&order, int n) {
  if(adj[n].first) { return; }
  for(int i = 0; i < adj[n].second.size(); ++i) {
    dfs(adj, order, adj[n].second[i]);
  }
  order.push_back(n);
  adj[n].first = true;
}     

vector<int> toposort(vector<pair<bool, vector<int>>>& adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  for(int i = 0; i < adj.size(); ++i) {
    if(adj[i].first) {continue;}
    dfs(adj, order, i);
  }
  return order;
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
  vector<int> order = toposort(adj);
  std::reverse(std::begin(order), std::end(order));
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
