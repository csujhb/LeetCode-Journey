# 力扣 11. 盛最多水的容器 学习笔记

##  题目描述

给定一个长度为 `n` 的整数数组 `height`。 
数组中第 `i` 条线段的两个端点分别为：

- `(i, 0)`
- `(i, height[i])`

从中找出两条线段，使它们与 `x` 轴共同构成的容器可以容纳最多的水。

返回这个容器可以储存的最大水量。

**说明：不能倾斜容器。**

---

## 题目本质

这道题本质上是在求：

```text
任意两条竖线之间所能形成的最大面积
```

如果选择下标为 `i` 和 `j` 的两条线，那么容器面积为：

```text
面积 = 宽度 × 高度
     = (j - i) × min(height[i], height[j])
```

其中：

* 宽度由横坐标差决定：`j - i`
* 高度由较短的那条线决定：`min(height[i], height[j])`

---

##  暴力解法

最直接的想法是枚举所有两条线段：

* 第一条线 `i`
* 第二条线 `j`
* 计算面积
* 取最大值

### 暴力代码思路

```c
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        area = (j - i) * min(height[i], height[j]);
        更新最大值;
    }
}
```

### 时间复杂度

$$O(n^2)$$

因为要枚举所有线对。

当 `n` 很大时会比较慢，因此需要更优解法。

---

##  最优解法：双指针

### 核心思想

使用两个指针：

* `left` 指向最左边
* `right` 指向最右边

每次计算当前这两条线组成的面积，然后移动较短的一边。


---

##  为什么要移动较短的一边

假设当前两条线高度分别为：

* `height[left]`
* `height[right]`

当前面积是：

```text
(right - left) × min(height[left], height[right])
```

### 情况 1：左边更短

如果：

```text
height[left] < height[right]
```

那么当前容器高度由左边决定。

此时如果移动右边：

* 宽度变小
* 高度仍然最多受左边限制

所以面积不可能变大。

只有移动左边，才有可能找到更高的线，从而提高容器高度。

---

### 情况 2：右边更短

同理，如果右边更短，就应该移动右边。

---

### 情况 3：两边一样高

如果两边一样高：

* 移动左边可以
* 移动右边也可以

标准写法通常只移动一边即可。

---

##  双指针算法步骤

1. 初始化：
   * `left = 0`
   * `right = n - 1`
   * `maxArea = 0`

2. 当 `left < right` 时循环：
   * 计算当前面积
   * 更新最大值
   * 移动较短的一边

3. 最后返回 `maxArea`

---

## C 语言标准写法

```c
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
        } else {
            right--;
        }
    }

    return maxArea;
}
```

---

## 代码逐句解析

### 初始化左右指针

```c
int left = 0;
int right = heightSize - 1;
```

表示从数组两端开始尝试，因为两端距离最远，宽度最大。

### 保存最大面积

```c
int maxArea = 0;
```

用于记录遍历过程中得到的最大容器面积。

### 主循环

```c
while (left < right)
```

只要左右指针没有相遇，就还能组成容器。

### 计算当前容器高度

```c
int h = height[left] < height[right] ? height[left] : height[right];
```

容器高度由短板决定，因此取两者较小值。

### 计算当前面积

```c
int area = (right - left) * h;
```

公式就是：`面积 = 宽度 × 高度`。

### 更新最大值

```c
if (area > maxArea) {
    maxArea = area;
}
```

如果当前面积更大，就更新答案。

### 移动较短的一边

```c
if (height[left] < height[right]) {
    left++;
} else {
    right--;
}
```

原因：
* 移动较长边没有意义
* 只有移动较短边，才有希望增大高度

---

##  示例分析

### 示例 1

输入：`height = [1,8,6,2,5,4,8,3,7]`

### 初始状态

* `left = 0`，高度 `1`
* `right = 8`，高度 `7`

面积：`(8 - 0) × min(1, 7) = 8 × 1 = 8`

最大面积更新为 `8`。因为左边更短，所以左指针右移。

---

### 第二轮

* `left = 1`，高度 `8`
* `right = 8`，高度 `7`

面积：`(8 - 1) × min(8, 7) = 7 × 7 = 49`

最大面积更新为 `49`。因为右边更短，所以右指针左移。

---

继续这样进行，最终得到最大面积：`49`

---

##  时间复杂度与空间复杂度

### 时间复杂度

$$O(n)$$

因为两个指针都只向中间移动，每个元素最多被访问一次。

### 空间复杂度

$$O(1)$$

只使用了常数个变量。

---

##  为什么双指针优于暴力法

### 暴力法

* 需要枚举所有两条线的组合
* 时间复杂度 $$O(n^2)$$

### 双指针法

* 利用面积公式和“短板效应”
* 每次排除一部分不可能更优的情况
* 时间复杂度 $$O(n)$$

因此双指针是这题的最优解法。

---

## 进一步的小优化：跳过无效高度

在标准双指针基础上，还可以做一个常数级优化。

如果当前左边较短，高度为 `hl`，那么左指针右移后，凡是满足 `height[left] <= hl` 的位置都可以直接跳过。

因为：
* 宽度变小了
* 高度没有变高

所以面积不可能超过当前值。

### 优化写法

```c
int maxArea(int* height, int heightSize) {
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
}
```

---

## 你原代码的分析

你原来的代码是：

```c
int maxArea(int* height, int heightSize) {
    int left=0;
    int right=heightSize-1;
    int area=0;
    int maxarea=0;
    while(left<right)
    {
        if(height[left]<height[right]){
            area=(right-left)*height[left];
            left++;
        }
        else if(height[left]>height[right]){
            area=(right-left)*height[right];
             right--;
        }  
        else{
            area=(right-left)*height[left];
            left++;
            right--;
        }
        if(area>maxarea)
         maxarea=area;
    }
    return maxarea;
}
```

### 这段代码的优点

* 思路正确
* 采用了双指针
* 时间复杂度也为 $$O(n)$$
* 大部分情况下都能正确运行

### 这段代码可以改进的地方

####  面积计算重复

你在 `if / else if / else` 中分别写了面积计算，存在重复。

#### 计算面积和移动指针混在一起

更推荐先统一计算面积，再统一决定移动哪边，逻辑更清晰。

#### 相等时同时移动两边

虽然通常也能得到正确答案，但标准写法一般只移动一边，更规范。

---

## 推荐写法与原写法对比

### 推荐写法

* 结构清晰，代码更简洁。
* 更符合双指针标准模板，面试中更容易解释。

---

## 易错点总结

### 易错点 1：误以为要移动较长边
应移动较短边，因为当前面积受短板限制。

### 易错点 2：相等时同时移动两边
虽然很多时候也能过，但标准解一般只移动一边，更稳妥。

### 易错点 3：忘记高度取最小值
容器高度不是较高边，而是较短边：`min(height[left], height[right])`

### 易错点 4：用暴力法导致超时
暴力法复杂度 $$O(n^2)$$，而双指针为 $$O(n)$$。

---

## 面试回答模板

如果面试官问你这题思路，可以这样回答：

> 这题可以用双指针。
> 左右指针分别从数组两端向中间移动，每次计算当前两条线形成的容器面积。
> 面积由宽度和短板决定，因此如果想获得更大面积，只能移动较短的一边，因为移动较长边只会让宽度减小，而短板不变，不可能得到更优解。
> 整个过程中每个元素最多访问一次，所以时间复杂度为 $$O(n)$$，空间复杂度为 $$O(1)$$。

---

##  一句话总结

这道题的核心是：

> **面积由短板决定，因此每次移动较短的一边，用双指针在线性时间内找到最大面积。**