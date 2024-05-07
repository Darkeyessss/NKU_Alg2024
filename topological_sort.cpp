/*
假设给我们一个任意的图，它可能是也可能不是DAG（有向无圈图），推广拓扑排序算法，以使得给定有向图G的输入，它的输出是以下两者之一：

一个拓扑排序，于是确定了G为DAG；
G中的一个圈，于是确定了G不是DAG.
输入格式：

First line: n vertices, m directed edges;

Following m lines, x y means edge from vertex x to vertex y

样例1：

Input:
5 5
1 2
1 3
2 5
3 4
4 5

Output:
YES                    //(DAG)
1,2,3,4,5              //(Topology Ordering)
样例2：

5 7
1 2
1 3
2 1
2 5
3 4
4 2
4 5

Output
NO                    //(Not A DAG)
1,3,4,2,1             //(Cycle)
测试数据范围：(n<=50,m<2500)

注意到输出的解可能不是唯一的。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Graph
{
public:
    int V;
    vector<vector<int>> adj;
    vector<int> inDegree;
    vector<bool> visited;
    vector<int> parent;
    vector<int> cycle;

    Graph(int V) : V(V), adj(V), inDegree(V, 0), visited(V, false), parent(V, -1) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        inDegree[v]++;
    }

    bool kahn()
    {
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }

        int cnt = 0;
        vector<int> topOrder;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            topOrder.push_back(u);

            for (int v : adj[u])
            {
                if (--inDegree[v] == 0)
                    q.push(v);
            }
            cnt++;
        }

        if (cnt != V)
        {
            return false; // 不是DAG
        }

        cout << "YES" << endl;
        for (int i = 0; i < topOrder.size(); i++)
        {
            if (i == topOrder.size() - 1)
            {
                cout << topOrder[i] + 1;
                break;
            }
            cout << topOrder[i] + 1 << ",";
        }

        cout << endl;
        return true;
    }

    bool dfs(int u)
    {
        visited[u] = true;
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                parent[v] = u;
                if (dfs(v))
                    return true;
            }
            else if (parent[u] != v)
            { // 找圈
                int at = u;
                cycle.push_back(u);
                while (parent[at] != -1 && at != v)
                {
                    at = parent[at];
                    cycle.push_back(at);
                    if (cycle.size() > V)
                    { // 检查
                        return false;
                    }
                }
                cycle.push_back(v);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        return false;
    }
    // 联合判断
    void findCycle()
    {
        for (int i = 0; i < V; ++i)
        {
            if (!visited[i] && dfs(i))
            {
                cout << "NO" << endl;
                for (int j = 0; j < cycle.size(); j++)
                {
                    cout << cycle[j] + 1 << ",";
                }
                cout << cycle[0] + 1;
                cout << endl;
                return;
            }
        }
    }
};

int main()
{
    int n, e;
    cin >> n >> e;
    Graph p(n);
    for (int i = 0; i < e; i++)
    {
        int in, out;
        cin >> in >> out;
        if (in == out) // 自环
        {
            cout << "NO" << endl
                 << in << "," << out;
            return 0;
        }
        p.addEdge(in - 1, out - 1);
    }

    if (!p.kahn())
    {
        p.findCycle();
    }

    return 0;
}