#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>

using namespace std;

// 读取txt文件
vector<double> read_txt(const string &name)
{
    vector<double> price;
    ifstream file(name);
    string line;
    getline(file, line); // 跳过标题
    while (getline(file, line))
    {
        // 替换所有双引号对为单引号
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i] == '"' && line[i + 1] == '"')
            {
                line.erase(i, 1);
            }
        }

        vector<string> tokens;
        string token;
        stringstream ss(line);
        while (getline(ss, token, ';'))
        {
            tokens.push_back(token);
        }

        if (tokens.size() == 12) // 确保有12个字段
        {
            price.push_back(stod(tokens[8])); // 提取收盘价
        }
    }

    return price;
}

// trade类，交易的结果
struct Trade
{
    int buy_day;
    int sell_day;
    double profit;
};

// 动态规划
Trade optimize(const vector<double> &price, double cost, int max)
{
    int n = price.size();

    vector<vector<double>> dp(n, vector<double>(max + 1, 0));
    vector<vector<int>> decision(n, vector<int>(max + 1, 0));

    for (int t = 1; t <= max; ++t)
    {
        double min_price = price[0];
        for (int i = 1; i < n; ++i)
        {
            min_price = min(min_price, price[i] - dp[i - 1][t - 1] - cost);
            double potential_profit = price[i] - min_price - cost;
            if (potential_profit > dp[i - 1][t])
            {
                dp[i][t] = potential_profit;
                decision[i][t] = 1;
            }
            else
            {
                dp[i][t] = dp[i - 1][t];
            }
        }
    }

    double best_profit = dp[n - 1][max];
    vector<int> time;
    int t = max;
    for (int i = n - 1; i > 0; --i)
    {
        if (decision[i][t] == 1)
        {
            time.push_back(i);
            --t;
        }
    }
    reverse(time.begin(), time.end());

    return {time.front(), time.back(), best_profit};
}
// 计算夏普比率
double sharpe(const vector<double> &price, double rate)
{
    vector<double> returns(price.size() - 1);
    for (size_t i = 1; i < price.size(); ++i)
    {
        returns[i - 1] = (price[i] - price[i - 1]) / price[i - 1];
    }

    double mean = accumulate(returns.begin(), returns.end(), 0) / returns.size();
    double excess = mean - rate / 252.0;

    double stddev = 0;
    for (const auto &ret : returns)
    {
        stddev += pow(ret - mean, 2);
    }
    stddev = sqrt(stddev / returns.size());

    return excess / stddev * sqrt(252);
}

//计算最大回撤
double max_drawdown(const vector<double> &price)
{
    double peak = price[0];
    double max_dd = 0;
    for (const auto &price : price)
    {
        peak = max(peak, price);
        double drawdown = (peak - price) / peak;
        max_dd = max(max_dd, drawdown);
    }
    return max_dd;
}

int main()
{
    string name = "Bitcoin_2023_1_24-2024_1_24_historical_data_coinmarketcap.txt";
    double cost = 0.001; // 每次交易的成本比例
    int max = 10;        // 最大交易次数
    double rate = 0.01;  // 无风险利率
    cin >> cost >> max;
    vector<double> price = read_txt(name);

    if (price.empty())
    {
        cerr << "Error: No valid price data found." << endl;
        return 1;
    }

    Trade result = optimize(price, cost, max);
    double sharpe_ratio = sharpe(price, rate);
    double max_dd = max_drawdown(price);

    cout << "最大收益是: " << result.profit << endl
         << "买入日期索引: " << result.buy_day << ", 卖出日期索引: " << result.sell_day << endl
         << "夏普比率: " << sharpe_ratio << endl
         << "最大回撤: " << max_dd * 100 << "%" << endl;

    return 0;
}

