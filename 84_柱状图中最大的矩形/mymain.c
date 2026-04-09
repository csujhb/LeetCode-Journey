#define MAX(a,b) (((a)>(b))?(a):(b))
int largestRectangleArea(int* heights, int heightsSize) {
    if(heightsSize==1) return heights[0];
    int stack[heightsSize+2];
    int top=-1;
    int maxArea=0;
    stack[++top]=-1;
    stack[++top]=0;
    for(int i=1;i<heightsSize;i++){
        while(top!=0&&heights[i]<heights[stack[top]]){
            int tmp=heights[stack[top--]];
            maxArea=MAX(((i-stack[top]-1)*tmp),maxArea);
        }
        stack[++top]=i;
    }
    while(top!=0){
        int tmp=heights[stack[top--]];
        maxArea=MAX(((heightsSize-stack[top]-1)*tmp),maxArea);
    }
    return maxArea;
}