#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
struct exchange_point {
  int a, b;
  double rate, commission;
};

vector<exchange_point> conditions_of_exchange;
int n, m, s;
double v;
double currencies[101];
bool solve();

int main() {
  int a, b;
  double rab, cab, rba, cba;
  cin >> n >> m >> s >> v;
  currencies[s] = v;
  conditions_of_exchange.reserve(m);
  for (int i = 0; i < m; ++i) {
    cin >> a >> b >> rab >> cab >> rba >> cba;
    conditions_of_exchange.push_back({a, b, rab, cab});
    conditions_of_exchange.push_back({b, a, rba, cba});
  }
  if (solve()) {
    cout << "YES";
  } else {
    cout << "NO";
  }
  return 0;
}

bool solve() {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < conditions_of_exchange.size(); j++) {
      currencies[conditions_of_exchange[j].b] = max(currencies[conditions_of_exchange[j].b], 
      (currencies[conditions_of_exchange[j].a] - conditions_of_exchange[j].commission) * conditions_of_exchange[j].rate);
    }
  }
  for (int i = 0; i < conditions_of_exchange.size(); i++) {
    if ((currencies[conditions_of_exchange[i].a] - conditions_of_exchange[i].commission) 
    * conditions_of_exchange[i].rate > currencies[conditions_of_exchange[i].b])
      return true;
  }
  return false;
}
