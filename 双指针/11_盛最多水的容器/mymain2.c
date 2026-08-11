// 2026.8.3

int maxArea(int *height, int heightSize)
{
    int left = 0, right = heightSize - 1;
    int max = 0;
    int water = 0;
    while (left < right)
    {
        int wid = right - left;
        if (height[left] < height[right])
        {
            water = wid * height[left];
            left++;
        }
        else
        {
            water = wid * height[right];
            right--;
        }
        if (water > max)
            max = water;
    }
    return max;
}