#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Box {
  public:
    int length, width, height;
    Box(int _l, int _w, int _h) : length(_l), width(_w), height(_h) { }
};

auto comparer = [](const Box& a, const Box& b) {
  return a.length*b.width > b.length*b.width;
};

void process(const vector<Box>& boxes) {
  vector<int> agg;
  sort(boxes.begin(), boxes.end(), comparer);
  
}

int main() {
  stringstream ss;
  string line;
  int tc;

  ifstream fin("box-stacking.txt");
  getline(fin, line);
  ss << line;
  ss >> tc;

  for(int i=0;i < tc; ++i) {
    int nBox;
    vector<Box> vecBox;
    getline(fin, line);
    ss << line;
    ss >> nBox;
    
    for(int j=0;j<nBox; j++) {
      int l,w,h;
      getline(fin, line);
      ss << line;
      ss >> l >> w >> h;
      ss.clear();
      vecBox.push_back(Box(l,w,h));
      vecBox.push_back(Box(w,h,l));
      vecBox.push_back(Box(h,l,w));
      process(vecBox);
    }
    
  }
}
