/*
请完成G-S稳定匹配算法（由男方发起邀请）
第一行数据表示Man(Woman)的数目n
； 接下来的数据中，第一个n*n
 的数据块表示Man的优先列表； 另一个n*n
的数据块表示Woman的优先列表。

输出数据一行
个数，表示每个Man的匹配对象。

Sample
Input
5
2 1 4 5 3
4 2 1 3 5
2 5 3 4 1
1 4 3 2 5
2 4 1 5 3
5 1 2 4 3
3 2 4 1 5
2 3 4 5 1
1 5 4 3 2
4 2 5 3 1
Output:
1 3 2 5 4
*/

#include <iostream>
using namespace std;
class people
{
public:
    bool isfree;
    int date;
    people() { date = -1; }
    // people(bool is) : isfree(is) { date = -1; }
};
bool love(int MenNum, int *wml, int m, int m1)
{
    for (int i = 0; i < MenNum; i++)
    {
        if (wml[i] == m + 1) // index
            return true;
        if (wml[i] == m1 + 1)
            return false;
    }
    return true;
}
void GS_algorithm(int MenNum, int **manlist, int **womanlist)
{
    people *man = new people[MenNum];
    people *woman = new people[MenNum];
    int freemen = MenNum;
    for (int i = 0; i < MenNum; i++)
    {
        man[i].isfree = true;
        woman[i].isfree = true;
    }
    while (freemen)
    {
        int m;
        // man[m] is slected
        for (m = 0; m < MenNum; m++)
        {
            if (man[m].isfree)
            {
                break;
            }
        }
        int w;
        for (w = 0; w < MenNum; w++)
        {
            if (manlist[m][w] != -1)
            {
                if (woman[manlist[m][w] - 1].isfree)
                {
                    //(m,w) date
                    woman[manlist[m][w] - 1].isfree = false;
                    man[m].isfree = false;
                    woman[manlist[m][w] - 1].date = m;
                    man[m].date = manlist[m][w] - 1;
                    freemen--;
                    // cout << m << " " << manlist[m][w] - 1 << endl;
                }
                else
                {
                    int m1 = woman[manlist[m][w] - 1].date;
                    if (love(MenNum, womanlist[manlist[m][w] - 1], m1, m))
                    { // w loves m1 more than m
                        man[m].isfree = true;
                        man[m].date = -1;
                    }
                    else if (love(MenNum, womanlist[manlist[m][w] - 1], m, m1))
                    { // w loves m more than m1
                        //(m,w) date
                        woman[manlist[m][w] - 1].isfree = false;
                        man[m].isfree = false;
                        woman[manlist[m][w] - 1].date = m;
                        man[m].date = manlist[m][w] - 1;
                        // m1 free
                        man[m1].isfree = true;
                        man[m1].date = -1;
                    }
                }
                manlist[m][w] = -1;
                break;
            }
        }
    }
    int *rst = new int[MenNum];
    for (int i = 0; i < MenNum; i++)
    {
        if (i != MenNum - 1)
            cout << man[i].date + 1 << " "; // index+1
        else
            cout << man[i].date + 1;
    }
    delete[] man;
    delete[] woman;
    delete[] rst;
    return;
}

int main()
{
    int MenNum;
    cin >> MenNum;
    // initialize

    int **manlist = new int *[MenNum];
    int **womanlist = new int *[MenNum];

    for (int i = 0; i < MenNum; i++)
    {
        manlist[i] = new int[MenNum];
        womanlist[i] = new int[MenNum];
    }
    for (int i = 0; i < MenNum; i++)
    {
        for (int j = 0; j < MenNum; j++)
        {
            cin >> manlist[i][j];
        }
    }
    for (int i = 0; i < MenNum; i++)
    {
        for (int j = 0; j < MenNum; j++)
        {
            cin >> womanlist[i][j];
        }
    }

    for (int i = 0; i < MenNum; i++)
    {
        for (int j = 0; j < MenNum; j++)
        {
            cout << manlist[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < MenNum; i++)
    {
        for (int j = 0; j < MenNum; j++)
        {
            cout << womanlist[i][j] << " ";
        }
        cout << endl;
    }

    GS_algorithm(MenNum, manlist, womanlist);

    for (int i = 0; i < MenNum; i++)
    {
        delete[] manlist[i];
        delete[] womanlist[i];
    }
    delete[] manlist;
    delete[] womanlist;
    return 0;
}