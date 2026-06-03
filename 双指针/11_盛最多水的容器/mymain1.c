int maxArea(int *height, int heightSize)
{
    int left = 0;
    int right = heightSize - 1;
    int maxArea = -1;
    while (left < right)
    {
        int h = height[left] > height[right] ? height[right] : height[left];
        int area = h * (right - left);
        if (area > maxArea)
            maxArea = area;
        if (height[left] > height[right])
            right--;
        else
            left++;
    }
    return maxArea;
}