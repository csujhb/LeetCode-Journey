#include <stdlib.h>
#include <stdbool.h>
#define STACK_SIZE 10000
bool isValid(char* s) {
    char stack[STACK_SIZE];
    int top=-1;
    while(*s!='\0'){
        if(top!=-1) {
            char cur=stack[top];
            switch(*s){
                case ')':
                    if(cur!='(') return false;
                    top--;
                    break;
                case '}':
                    if(cur!='{') return false;
                    top--;
                    break;
                case ']':
                    if(cur!='[') return false;
                    top--;
                    break;
                default:
                    stack[++top]=*s;
                    break;
            }
            s++;
        }else{
            stack[++top]=*s;
            s++;
        }

    }
    if(top==-1)
    return true;
    else
    return false;
}
