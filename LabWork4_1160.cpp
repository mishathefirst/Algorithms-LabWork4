#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct node {
	node *root;

	int number;

	node(int n) :
		number(n),
		root(this) {};

	node *get_updated_root() {
		while (this -> root != this -> root -> root) 
			this -> root = this -> root -> root;
		return this -> root;
	};
};

struct connection {
	node *first_node;
	node *second_node;

	int value;

	connection(node *first_node, node *second_node, int value) :
		first_node(first_node),
		second_node(second_node),
		value(value) {};
};

vector<node> nodes;
vector<connection> connections, network;
int n, m, a, b, value, max_value = 0;

int main() {

	cin >> n >> m;

	nodes.reserve(n);
	connections.reserve(m);
	network.reserve(m);

	for (int i = 0; i < n; i++) {
		nodes.emplace_back(i + 1);
	}
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> value;
		connections.emplace_back(&nodes[a - 1], &nodes[b - 1], value);
	}

	sort(connections.begin(), connections.end(), [](connection a, connection b) { return a.value < b.value; });

	for (auto connection : connections) 
		if (connection.first_node -> get_updated_root() != connection.second_node -> get_updated_root()) {
			connection.first_node -> root -> root = connection.second_node -> root -> root;
			network.push_back(connection);

			max_value = max(max_value, connection.value);
		}

	cout << max_value << endl;
	cout << network.size() << endl;
	for (auto connection : network)
		cout << connection.first_node -> number << " " << connection.second_node -> number << endl;

	return 0;
}