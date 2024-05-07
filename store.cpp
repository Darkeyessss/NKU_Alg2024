/*
问题描述:
设有
个程序
要存放在长度为
的磁带上. 程序
存放在磁带上的长度为
,
. 程序存储问题要求确定这
个程序在磁带上的一个存储方案,使得能够在磁带上存储尽可能多的程序。

编程任务:

对于给定的n个程序存放在磁带上的长度,编程计算磁带上最多可以存储的程序数。

数据输入:

第一行是2个整数,分别表示文件个数
和磁带的长度
.接下来的一行中,有
个正整数,表示程序存放在磁带上的长度。 (
,
)

结果输出:

将编程计算出的最多可以存储的程序数输出。

输入示例

6 50

2 3 13 8 80 20

输出示例

5
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, L;
    cin >> n >> L;
    vector<int> length;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        length.push_back(tmp);
    }
    sort(length.begin(), length.end(), greater<int>());
    int cnt = 0;
    while (L >= 0)
    {
        if (length.empty())
        {
            break;
        }
        if (L < length.back())
        {
            break;
        }
        else
        {
            L -= length.back();
            length.pop_back();
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}