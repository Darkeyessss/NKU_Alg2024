/*
题目描述
给定一个 n 次多项式 F(x)，和一个 m 次多项式 G(x)
请求出 F(x) 和 G(x)的卷积。
输入格式
第一行两个整数 n,m。
接下来一行 n + 1个数字，从高到低表示 F(x)的系数。
接下来一行 m +1个数字，从高到低表示 G(x)的系数。
保证输入中的系数大于等于 0 且小于等于 9.
对于 100% 的数据:1 ≤ n,m < 10^5
输出格式
行 n + m + 1个数字，从高到低表示 F(x)*G(x)的系数。
样例输入 #1
5 5
6 5 4 3 2 1
1 1 1 1 1 1
样例输出 #1
6 11 15 18 20 21 15 10 6 3 1
*/
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

using namespace std;

const double PI = M_PI;

void fft(vector<complex<double>> &a, bool invert)
{
    int n = a.size();
    if (n == 1)
        return;

    vector<complex<double>> a0(n / 2), a1(n / 2); // 分为奇偶递归操作
    for (int i = 0; i < n / 2; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1); // 蝴蝶操作
    complex<double> w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; i++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
        {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> &F, vector<int> &G)
{
    vector<complex<double>> fa(F.begin(), F.end()), fb(G.begin(), G.end());
    int n = 1;
    while (n < F.size() + G.size()) // 扩充长度
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = int(fa[i].real() + 0.5); // 四舍五入取整
    return result;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> F(n + 1), G(m + 1);
    for (int i = 0; i <= n; i++)
        cin >> F[i];
    for (int i = 0; i <= m; i++)
        cin >> G[i];

    vector<int> result = multiply(F, G);

    for (int i = 0; i < m + n + 1; i++)
    {
        if (i > 0)
            cout << " ";
        cout << result[i];
    }

    return 0;
}
