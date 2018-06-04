#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void run(vector<pair<bool, vector<int>>> &adj, int n) {
  if(adj[n].first) {return;}
  adj[n].first = true;
  for(int i = 0; i < adj[n].second.size(); ++i) {
    run(adj, adj[n].second[i]);
  }
}

int number_of_components(vector<pair<bool, vector<int>>> &adj) {
  int res = 0;
  for(int i = 0; i < adj.size(); ++i){
    if(adj[i].first) {continue;}
    ++res;
    run(adj, i);
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<pair<bool, vector<int>>> adj(n);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].first = false;
    adj[y - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
    adj[y - 1].second.push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
