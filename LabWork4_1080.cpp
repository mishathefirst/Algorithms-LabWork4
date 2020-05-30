#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int n, c;

int main()
{

    cin >> n;
    vector<bool> element_neighbours(n, false);
    vector<vector<bool>> graph(n, element_neighbours);
    vector<int> colour_selection(n, -1);
    for (int i = 0; i < n; i++)
    {
        while (cin >> c && c)
        {
            c--;
            graph[i][c] = true;
            graph[c][i] = true;
        }
    }

    queue<int> elements_queue;
    elements_queue.push(0);
    colour_selection[0] = 0;
    bool possibility_flag = true;
    while (!elements_queue.empty() && possibility_flag)
    {
        int node = elements_queue.front();
        elements_queue.pop();
        for (int i = 0; i < n; i++)
        {
            if (colour_selection[i] == colour_selection[node] && graph[node][i])
            {
                possibility_flag = false;
                break;
            }
            if (colour_selection[i] == -1 && graph[node][i])
            {
                if (colour_selection[node] == 1){
                    colour_selection[i] = 0;
                }
                else{
                    colour_selection[i] = 1;
                }
                elements_queue.push(i);
            }
        }
    }

    if (!possibility_flag)
        cout << -1;
    else
        for (int i = 0; i < n; i++)
            cout << colour_selection[i];
    return 0;
}