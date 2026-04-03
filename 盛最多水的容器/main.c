int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int maxArea = 0;

    while (left < right) {
        int h = height[left] < height[right] ? height[left] : height[right];
        int area = (right - left) * h;

        if (area > maxArea) {
            maxArea = area;
        }

        if (height[left] < height[right]) {
            left++;
        }
        else {
            right--;
        }
    }

    return maxArea;
}



/*int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int maxArea = 0;

    while (left < right) {
        int hl = height[left];
        int hr = height[right];
        int h = hl < hr ? hl : hr;
        int area = (right - left) * h;

        if (area > maxArea) {
            maxArea = area;
        }

        if (hl < hr) {
            while (left < right && height[left] <= hl) {
                left++;
            }
        } else {
            while (left < right && height[right] <= hr) {
                right--;
            }
        }
    }

    return maxArea;
}*/
