// 2026.8.12

int maxProfit(int *prices, int pricesSize)
{
    int res = 0;
    for (int i = 0; i < pricesSize; i++)
    {
        int left = i;
        while (i < pricesSize - 1 && prices[i] < prices[i + 1])
        {
            i++;
        }
        if (i != left)
        {
            res += prices[i] - prices[left];
        }
    }
    return res;
}

// 标准做法：把所有正收益 prices[i] - prices[i-1] 全部累加。
int maxProfit(int *prices, int pricesSize)
{
    int profit = 0;

    for (int i = 1; i < pricesSize; i++)
    {
        if (prices[i] > prices[i - 1])
        {
            profit += prices[i] - prices[i - 1];
        }
    }

    return profit;
}