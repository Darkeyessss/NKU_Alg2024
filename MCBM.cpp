/*
题目背景
第二次世界大战期间，英国皇家空军从沦陷国征募了大量外籍飞行员。由皇家空军派出的每一架飞机都需要配备在航行技能和语言上能互相配合的两名飞行员，其中一名是英国飞行员，另一名是外籍飞行员。在众多的飞行员中，每一名外籍飞行员都可以与其他若干名英国飞行员很好地配合。
题目描述
一共有”个飞行员，其中有 个外籍飞行员和(n - m)个英国飞行员，外籍飞行员从 1 到 m 编号，英国飞行员从 m +1到” 编号。 对于给定的外籍飞行员与英国飞行员的配合情况，试设计一个算法找出最佳飞行员配对方案，使皇家空军一次能派出最多的飞机。
输入格式
输入的第一行是用空格隔开的两个正整数，分别代表外籍飞行员的个数 m 和飞行员总数 ”。
从第二行起到倒数第二行，每行有两个整数 …,v，代表外籍飞行员 u 可以和英国飞行员 υ 配合。
输入的最后一行保证为 -1 -1，代表输入结束。
输出格式
本题存在 Special Judge。请输出能派出最多的飞机数量，并给出一种可行的方案。输出的第一行是一个整数，代表一次能派出的最多飞机数量，设这个整数是 k。第2 行到第k+1行，每行输出两个整数u,v，代表在你给出的方案中，外籍飞行员u 和英国飞行员v配合。这k 行的 u与v应该互不相同。
样例 #1
样例输入 #1
5 10
1 7
1 8
2 6
2 9
2 10
3 7
3 8
4 7
4 8
5 10
-1 -1
样例输出 #1
4
1 7
2 9
3 8
5 10
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> graph[100]; // 邻接表
bool flow[100][100];    // 边的容量
int parent[100];

bool bfs(int begin, int end)
{
    memset(parent, -1, sizeof(parent));
    vector<int> tmp;
    tmp.push_back(begin);

    vector<bool> visited(100, false);
    visited[begin] = true;

    while (!tmp.empty())
    {
        int u = tmp.front();
        tmp.erase(tmp.begin());

        for (int v : graph[u])
        {
            if (!visited[v] && flow[u][v]) // 流量没到0
            {
                tmp.push_back(v);
                parent[v] = u;
                visited[v] = true;
                if (v == end)
                    return true;
            }
        }
    }
    return false;
}

int ford_Fulkerson(int begin, int end)
{
    int max_flow = 0;

    while (bfs(begin, end))
    {
        for (int v = end; v != begin; v = parent[v]) // 回溯
        {
            int u = parent[v];
            flow[u][v] = false; // 正向路径减
            flow[v][u] = true;  // 反向路径加
        }
        max_flow += 1;
    }
    return max_flow;
}

int main()
{
    int m, n;
    cin >> m >> n;

    int begin = 0;
    int end = n + 1;

    memset(flow, 0, sizeof(flow)); // 初始化容量矩阵为 false

    for (int i = 1; i <= m; i++) // 外籍
    {
        graph[begin].push_back(i);
        graph[i].push_back(begin);
        flow[begin][i] = true;
    }

    for (int i = m + 1; i <= n; i++) // 英国
    {
        graph[i].push_back(end);
        graph[end].push_back(i);
        flow[i][end] = true;
    }

    while (true)
    {
        int u, v;
        cin >> u >> v;
        if (u == -1 && v == -1)
            break;
        graph[u].push_back(v);
        graph[v].push_back(u);
        flow[u][v] = true;
    }

    int max_plane = ford_Fulkerson(begin, end);
    cout << max_plane << endl;

    for (int u = 1; u <= m; ++u)
    {
        for (int v = m + 1; v <= n; ++v)
        {
            if (flow[v][u])
            {
                cout << u << " " << v << endl;
            }
        }
    }

    return 0;
}
