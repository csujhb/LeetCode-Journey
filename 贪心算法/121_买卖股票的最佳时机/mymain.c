int maxProfit(int *prices, int pricesSize)
{
    int max = 0;
    int minPrice = 10001;
    for (int i = 0; i < pricesSize; i++)
    {
        if (prices[i] - minPrice > max)
            max = prices[i] - minPrice;
        if (minPrice > prices[i])
            minPrice = prices[i];
    }
    return max;
}