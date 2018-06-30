#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>

using std::vector;
using std::pow;
using std::priority_queue;

struct Edge {
  int from;
  int to;
  double length;
};

struct Point {
  int x,y, index;
  bool added = false;
  void inspect() {std::cout << "(" << x <<":"<<y<<")";}
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

vector<double> step_point(vector<Point>& points, int current, vector<double>& weights) {
  points[current].added = true;
  // std::cout<<"step " << current << points[current].added << "\n";
  auto cmp = [&points, &current](Point left, Point right) { 
    return length_between(points[current].x, points[current].y, left.x, left.y) >
      length_between(points[current].x, points[current].y, right.x, right.y);
  };
  priority_queue<Point, vector<Point>, decltype(cmp)> h(cmp);
  for(int i = 0; i < points.size(); ++i) {
    if(points[i].added) {continue;}
    h.push(points[i]);
  }
      // std::cout<<"cur:" << current << "\n";
      double l; 
  while(!h.empty()) {
    Point p = h.top();
    h.pop();
    if(p.added) {continue;}
    l = length_between(points[current].x, points[current].y, p.x, p.y);
    if(weights[p.index] > l) {
      // p.inspect();
    // std::cout<<std::endl;
    // std::cout << "set for "<< p.index <<" " << length_between(points[current].x, points[current].y, p.x, p.y) << "\n";
    
      weights[p.index] = l ;
      step_point(points, p.index, weights);
    }
    
  }
  return weights;
}

double minimum_distance(vector<Point>& points) {
  double result = 0.;
  vector<double> w(points.size());
  for(int i = 0; i < w.size(); ++i){
    w[i] =  std::numeric_limits<int>::max();
  }
  w[0] = 0;

  w = step_point(points, 0, w);
  for(auto a: w) {
    // std::cout << a << ' ';
    result += a;
  }
  // std::cout << std::endl;
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<Point> points;
  for (size_t i = 0; i < n; i++) {
    Point p = Point();
    p.index = i;
    std::cin >> p.x >> p.y;
    points.push_back(p);
  }
  std::cout << std::setprecision(10) << minimum_distance(points) << std::endl;
}
