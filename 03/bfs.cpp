#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;

int run(vector<pair<bool, vector<int>>> &adj, queue<int>& q, int from, int to, int lvl) {
  std::cout << from + 1 << "\n";
  if(from == to) { return lvl; }
  if(adj[from].first) { return -1; }
  std::cout << "!\n";
  adj[from].first = true;
  for(int i = 0; i < adj[from].second.size(); ++i) {
    int a = adj[from].second[i];
    if(!adj[a].first) {
      q.push(a);
    }  
  }
  std::cout<<"?\n";
  while(!(q.size() != 0)) {
    int r = run(adj, q, q.front(), to, ++lvl);
    std::cout<< "size:" << q.size() << "\n";
    if(r != -1) return r;
    q.pop();
  }
  
  return -1;
}

int distance(vector<pair<bool, vector<int>>> &adj, int from, int to) {
  queue<int> q = {};
  return run(adj, q, from, to, 0);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<pair<bool, vector<int>>> adj(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].first = false;
    adj[y - 1].first = false;
    adj[x - 1].second.push_back(y - 1);
    adj[y - 1].second.push_back(x - 1);
  }
  int from, to;
  std::cin >> from >> to;
  from--, to--;
  std::cout << distance(adj, from, to);
}
