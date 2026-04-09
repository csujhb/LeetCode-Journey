#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
    int max=0;
    for (int i = 0; i < numsSize; i++)
    {
        if(max>=i){
            max=(max>(nums[i]+i)?max:(nums[i]+i));
        }else{
            return false;
        }
    }
    return true;
    
}