
int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int area = 0;
    int maxarea = 0;
    while (left < right)
    {
        if (height[left] < height[right]) {
            area = (right - left) * height[left];
            left++;
        }
        else if (height[left] > height[right]) {
            area = (right - left) * height[right];
            right--;
        }
        else {
            area = (right - left) * height[left];
            left++;
            right--;
        }
        if (area > maxarea)
            maxarea = area;
    }
    return maxarea;
}
