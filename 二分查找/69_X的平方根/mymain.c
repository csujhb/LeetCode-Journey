// 2026.8.5
int mySqrt(int x)
{
    if (x == 0 || x == 1)
        return x;
    int left = 1, right = x;
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2;
        if (mid * mid > x)
        {
            right = mid - 1;
        }
        else if (mid * mid <= x) // mid*mid可能会溢出，不对
        {
            left = mid;
        }
    }
    return left;
}

int mySqrt(int x)
{
    if (x == 0)
        return 0;
    int left = 1, right = x;
    while (left < right)
    {
        int mid = left + (right - left + 1) / 2; // 取右中位数
        if (mid <= x / mid)
        {
            left = mid; // 收缩左边界
        }
        else
        {
            right = mid - 1; // 收缩右边界
        }
    }
    return left;
}