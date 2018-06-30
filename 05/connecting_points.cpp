#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>

using std::vector;
using std::pow;

struct Edge {
  int from;
  int to;
  double length;
};

double length_between(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

vector<vector<Edge>> edges(vector<int> x, vector<int> y) {
  vector<Edge> es;
  Edge e;
  double l;
  for(int i = 0; i < x.size() -1 ; ++i) {
    for(int j = i + 1; j < x.size(); ++j) {
      l = length_between(x[i], y[i], x[j], y[j]);
      e = Edge();
      e.from = i;
      e.to = j;
      
      e.length = l;
      es.push_back(e);
      e = Edge();
      e.from = j;
      e.to = i;
      
      e.length = l;
      es.push_back(e);

    }
  }

  // std::cout<< es.size()<<std::endl;
  auto cmp = [](Edge left, Edge right) { return left.length < right.length; };
  std::sort(es.begin(), es.end(), cmp);
  vector<vector<Edge>> mapped(x.size());
  for(auto e: es) {
    mapped[e.from].push_back(e);
  }
  return mapped;
}

vector<double> step(vector<vector<Edge>>& es, int current, vector<double>& weights) {
  for(auto e : es[current]) {

    if(weights[e.to] > e.length) {
      std::cout<< "to(" << e.from << ":" << e.to << ":" << e.length <<")\n";

      weights[e.to] = e.length;
      step(es, e.to, weights);
    }
  }
  return weights;
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  // std::cout<< x.size() << std::endl;
  vector<bool> added(x.size());
  vector<vector<Edge>> es = edges(x, y);
  vector<double> w(x.size());
  for(int i = 0; i< w.size(); ++i) {w[i] = std::numeric_limits<int>::max();}
  w[0] = 0;
  w = step(es, 0, w);
  
  for(auto b : w) {
    std::cout << b << " ";
    result += b;
  }
  std::cout << std::endl;
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
