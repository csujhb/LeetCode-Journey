#define MAX(a,b) (((a)>(b))?(a):(b))
int jump(int* nums, int numsSize) {
    if(numsSize==1) return 0;
    int steps=0;
    int maxDis=0;
    int right=0;
    for(int left=0;left<numsSize;){
        while(left<=right){
            maxDis=MAX(maxDis,nums[left]+left);
            left++;
        }
        steps++;
        if(maxDis<numsSize-1){
            right=maxDis;
        }else{
            return steps;
        }
    }
    return -1;
}