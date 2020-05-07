#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Box {
  public:
    int length, width, height;
    Box(int _l, int _w, int _h) : length(_l), width(_w), height(_h) { }
    Box& operator=(const Box& a) {
      if(this == &a) {
        return *this;
      }
      this->length = a.length;
      this->width = a.width;
      this->height = a.height;
      return *this;
    }
    friend ostream& operator<<(ostream& out, const Box& b) {
      out << b.length << " " << b.width << " " << b.height << endl;
      return out;
    }
};

auto comparer = [](const Box& a, const Box& b) {
  return a.length*a.width < b.length*b.width;
};

int maxHeightOfStackedBoxes(vector<Box>& boxes) {
  vector<int> agg(boxes.size());
  sort(boxes.begin(), boxes.end(), comparer);
  for(int i=0; i < boxes.size(); ++i) {
    auto max = 0;
    for(int j=0; j < i; ++j) {
      auto lengthFitsWithLength = boxes[j].length < boxes[i].length && boxes[j].width < boxes[i].width;
      auto lengthFitsWithWidth = boxes[j].width < boxes[i].length && boxes[j].length < boxes[i].width;
      if((lengthFitsWithLength || lengthFitsWithWidth) && max < agg[j]) {
        max = agg[j];
      }
    }
    agg[i] = max + boxes[i].height;
  }
  return *max_element(begin(agg), end(agg));
}

int main() {
  stringstream ss;
  string line;
  int tc;

  ifstream fin("box-stacking.txt");
  getline(fin, line);
  ss << line;
  ss >> tc;
  ss.clear();
  for(int i=0;i < tc; ++i) {
    int nBox;
    vector<Box> vecBox;
    getline(fin, line);
    ss << line;
    ss >> nBox;
    ss.clear();
    for(int j=0;j<nBox; j++) {
      int l,w,h;
      getline(fin, line);
      ss << line;
      ss >> l >> w >> h;
      ss.clear();
      vecBox.push_back(Box(l,w,h));
      vecBox.push_back(Box(w,h,l));
      vecBox.push_back(Box(h,l,w));
    }
    cout << maxHeightOfStackedBoxes(vecBox)<< endl;
  }
  fin.close();
}
