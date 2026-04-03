int trap(int* height, int heightSize) {
    int leftMax = 0;
    int rightMax = 0;
    int left = 0;
    int right = heightSize - 1;
    int water = 0;
    while (left < right) {
        if (height[left] > leftMax)  leftMax = height[left];
        if (height[right] > rightMax)  rightMax = height[right];
        if (leftMax < rightMax) {
            water += leftMax - height[left];
            left++;
        }
        else {
            water += rightMax - height[right];
            right--;
        }
    }
    return water;
}
