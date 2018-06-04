#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cout;
using std::endl;


int reach(vector<vector<pair<int, bool>> > &adj, int x, int y) {
  for(int i = 0; i < adj[x].size(); ++i) {
    if(adj[x][i].second) { continue; }
    if(adj[x][i].first == y) {
       return 1;
    }
    adj[x][i].second = true;
    if(reach(adj, adj[x][i].first, y) == 1) {return 1;}
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<pair<int, bool>> > adj(n, vector<pair<int, bool>>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back({y - 1, false});
    adj[y - 1].push_back({x - 1, false});
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
