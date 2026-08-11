
int maxProfit(int *prices, int pricesSize)
{
    int lowest = 10001;
    int max = 0;
    for (int i = 0; i < pricesSize; i++)
    {
        if (prices[i] - lowest > max)
            max = prices[i] - lowest;
        if (prices[i] < lowest)
            lowest = prices[i];
    }
    return max;
}