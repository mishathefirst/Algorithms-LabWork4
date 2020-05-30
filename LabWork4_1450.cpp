#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<int> node_connections[501], connection_values[501];
int values[501];
int N, M, S, F;

int solve(int start_point) {
	if (start_point == F) return 0;

	int &result = values[start_point];

	if (result == -1) {
		result = -2;

		for (int i = node_connections[start_point].size() - 1; i >= 0; --i) {
			int current_value = solve(node_connections[start_point][i]);

			if (current_value != -2) {
				current_value += connection_values[start_point][i];
				result = max(result, current_value);
			}
		}
	}

	return result;
}

int main() {

	cin >> N >> M;

	for (int i = 0, a, b, c; i < M; i++) {
		cin >> a >> b >> c;

		node_connections[a].push_back(b);
		connection_values[a].push_back(c);
	}

	for (int i = 0; i < 501; i++) values[i] = -1;

	cin >> S >> F;

	int final_result = solve(S);

	if (final_result == -2) cout << "No solution" << endl;
	else cout << final_result << endl;

	return 0;
}