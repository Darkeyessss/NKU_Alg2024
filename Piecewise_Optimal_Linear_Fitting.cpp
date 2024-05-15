/*
我们拟采用分段的直线拟合给定的n个数据点(2<n < 1000，对于第个数据点，
它的横坐标是xi，纵坐标是yi，满足|xi|< 1000，|yi|< 1000，保证所有数据点的横坐标都不相同)，
目标是使得罚分E+C·l最小，其中E为所有直线的高斯最小二乘误差之和，C是预先给定的权重(0 <C< 10^5)，
l是直线数量，请输出最小的罚分，精确到小数点后两位。
注意:横坐标连续的点才可以被分成一段，属于同一段的教据点共享同一条拟合直线，拟合直线与数据点段一一对应。
输入格式:
共n + 1行，第一行包含两个整数n和C，含义如题面所述。
对于接下来的几行，第i行包含两个整数心xi和yi，表示第i个数据点的坐标。

样例输入:
10 10000
21 937
241 930
389 942
469 945
525 941
538 955
540 957
701 967
743 964
969 970

样例输出：
10378.54
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct point
{
    double x, y;
};

bool bigger(point a, point b)
{
    return a.x > b.x;
}

// 计算从i到j的段的最小二乘误差
double E(const vector<point> &p, int i, int j)
{
    int n = j - i + 1;
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int k = i; k <= j; ++k)
    {
        sumX += p[k].x;
        sumY += p[k].y;
        sumXY += p[k].x * p[k].y;
        sumX2 += p[k].x * p[k].x;
    }

    double avgX = sumX / n;
    double avgY = sumY / n;

    double up = sumXY - sumX * avgY;
    double down = sumX2 - sumX * avgX;

    double a = up / down;
    double b = avgY - a * avgX;

    double error = 0;
    for (int k = i; k <= j; ++k)
    {
        double predictedY = a * p[k].x + b;
        error += (predictedY - p[k].y) * (predictedY - p[k].y);
    }

    return error;
}

int main()
{
    int n;
    double C;
    cin >> n >> C;

    vector<point> p(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i].x >> p[i].y;
    }

    sort(p.begin(), p.end(), bigger);

    vector<double> dp(n + 1, numeric_limits<double>::max());
    dp[0] = 0;

    for (int j = 1; j <= n; ++j)
    {
        for (int i = 0; i < j; ++i)
        {
            double error = E(p, i, j - 1);
            dp[j] = min(dp[j], dp[i] + error + C); // 状态转移方程
        }
    }

    cout << fixed << setprecision(2) << dp[n] << endl;

    return 0;
}
