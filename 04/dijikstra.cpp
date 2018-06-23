#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

vector<int>& run(vector<vector<int> > &adj, vector<vector<int> > &cost, int from, int to, vector<int>& result){
  // std::cout<< "in: " << from << "\n";
  if(from == to) { return result; }
  for(int i = 0; i< adj[from].size(); i++) {
    int child = adj[from][i];
    // std::cout<< "child: " << child << "\n";
    if(result[child] > result[from] + cost[from][i]) {
     result[child] = result[from] + cost[from][i];
     run(adj, cost, child, to, result);
   }
    
  }

  return result;
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int from, int to) {
  vector<int> result(adj.size());
  for(int i = 0; i < result.size(); ++i) {
    if(i == from) {result[i] = 0;} else { result[i] = std::numeric_limits<int>::max();}
  }
  int r = run(adj,cost, from, to, result)[to];
  
  return r == std::numeric_limits<int>::max() ? -1 : r;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
