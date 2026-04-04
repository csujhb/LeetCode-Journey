

#include <string.h>
#include<stdlib.h>
int isInclude(int* need, int* win) {
	for (int i = 0; i < 128; i++) {
		if (need[i] > 0 && need[i] > win[i]) {
			return 0;
		}
	}
	return 1;
}

char* minWindow(char* s, char* t) {
	if (strlen(s) < strlen(t)) return NULL;
	int left = 0;
	int right = 0;
	int need[128] = { 0 };
	int minleft = -1;
	int minright = -1;
	int window[128] = { 0 };
	int minLen = strlen(s);
	for (int i = 0; i < strlen(t); i++) {
		need[(int)t[i]]++;
	}
	while (right < strlen(s)) {
		window[(int)s[right]]++;
		if (isInclude(need, window)) {
			while (isInclude(need, window)) {			
				window[(int)s[left]]--;
				left++;
			}
			if (minLen > right - left + 2) {
				minLen = right - left + 2;
				minleft = left - 1;
				minright = right;
			}
			window[(int)s[right]]--;
		}
		else {
			right++;
		}
	}
	if ((minright - minleft + 2) <= 0) return NULL;
	char* result = (char*)malloc(sizeof(char) * (minright - minleft + 2));
	strncpy(result, s + minleft, minright - minleft + 1);
	result[minright - minleft + 1] = '\0';
	return result;
}
