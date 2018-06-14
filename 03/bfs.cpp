#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

using std::vector;
using std::queue;
using std::unordered_map;


int distance(vector<vector<int>> &adj, int from, int to) {
  unordered_map<int, int> dist;
  unordered_map<int, int> prev;

  for (size_t i = 0; i < adj.size(); ++i) {
    dist[i] = std::numeric_limits<int>::infinity();
    prev[i] = -1;
  }

  queue<int> q;

  q.push(from);
  dist[from] = 0;

  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    auto &edges = adj[u];

    for (auto e : edges) {
      if (dist[e] == std::numeric_limits<int>::infinity()) {
        q.push(e);
        dist[e] = dist[u] + 1;
        prev[e] = u;
      }
    }
  }

  if (prev[to] == -1) return -1;

  std::vector<int> result;

  while (to != from) {
    result.push_back(to);
    to = prev[to];
  }

  return result.empty() ? -1 : result.size();
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector< vector< int > > adj(n, vector< int >());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
  return 0;
}