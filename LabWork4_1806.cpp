#include <stdio.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>
#include <limits>
#include <iostream>

using namespace std;

const int width = 10;
const int maxn = 50000;
long long digit_reference[width];
int cost[width]; 

struct Node
{
	vector<pair<int, Node*>> available_nodes; 
	Node* parent; 
	int min_time; 
	bool visited; 
} 

nodes[maxn];

unordered_map<long long, Node*> m;

int getDigit(long long num, int i)
{ return num / digit_reference[i] % 10; }

long long setDigit(long long num, int i, int d)
{ return num - ((long long)getDigit(num, i)) * digit_reference[i] + d * digit_reference[i]; }

int matchPrefix(long long num1, long long num2)
{
	int matched = 0;
	for (int i = width - 1; i >= 0; i--)
		if (getDigit(num1, i) == getDigit(num2, i)) matched++;
			else break;
	
	return matched;
}

void add(long long num, int id)
{
	
	vector<pair<int, Node*>> available_nodes;

	for (int i = 0; i < width; i++)
		for (int d = 0; d < 10; d++)
		{
			auto num2 = setDigit(num, i, d);
			auto it = m.find(num2); 
			if (it != m.end())
			{
				int c = cost[matchPrefix(num, num2)];
				available_nodes.push_back({ c, (*it).second });
			}
		}
	
	
	for (int i = 0; i < width; i++)
		for (int j = i + 1; j < width; j++)
		{
			int di = getDigit(num, i);
			int dj = getDigit(num, j);
			auto num2 = setDigit(setDigit(num, j, di), i, dj);
			auto it = m.find(num2);
			if (it != m.end())
			{
				int c = cost[matchPrefix(num, num2)];
				available_nodes.push_back({ c, (*it).second });
			}
		}
	
	m[num] = &nodes[id];
	
	for (auto p : available_nodes)
	{
		p.second -> available_nodes.push_back({ p.first, &nodes[id] });
		nodes[id].available_nodes.push_back({ p.first, p.second });
	}
}


void search(Node* start, int N)
{
	const int inf = numeric_limits<int>::max() / 2;
	using pin = pair<int, Node*>;
	priority_queue<pin, vector<pin>, greater<pin>> q;

	for (int i = 0; i < N; i++)
		nodes[i].min_time = inf, nodes[i].visited = false;
	start -> min_time = 0;

	q.push({ 0, start });
	while (!q.empty())
	{
		auto p = q.top();
		q.pop();
		auto node = p.second;
		if (node -> visited)
			continue;
		node -> visited = true;
		for (auto it = node -> available_nodes.begin(); it < node -> available_nodes.end(); it++)
		{
			auto n = (*it).second;
			int cost = (*it).first;
			if (!n -> visited && n -> min_time > node -> min_time + cost)
			{
				n -> parent = node;
				n -> min_time = node -> min_time + cost;
				q.push({ n -> min_time, n});
			}
		}
	}
}

int main()
{
	
	long long b = 1;
	for (int i = 0; i < width; i++)
		digit_reference[i] = b, b *= 10;

	
	int n;
	cin >> n;
	for (int i = 0; i < width; i++)
		cin >> cost[i];
	for (int i = 0; i < n; i++)
	{
		long long num;
		cin >> num;
		
		add(num, i);
	}

	
	search(&nodes[0], n);

	
	if (!nodes[n - 1].visited)
	{
		cout << "-1";
		return 0;
	}
	cout << nodes[n - 1].min_time << endl;
	vector<Node*> result;
	for (Node* node = &nodes[n - 1]; node; node = node -> parent)
		result.push_back(node);
	cout <<  result.size() << endl;
	for (auto it = result.rbegin(); it < result.rend(); it++)
		cout << (1 + (*it - nodes)) << " ";
}