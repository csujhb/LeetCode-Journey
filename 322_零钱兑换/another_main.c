//广度优先搜索（BFS）
#include <stdlib.h>
#include <string.h>

int coinChange(int* coins, int coinsSize, int amount) {
    if (amount == 0) return 0;
    int *queue = (int*)malloc(sizeof(int) * (amount + 1));
    int *visited = (int*)calloc(amount + 1, sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = amount;
    visited[amount] = 1;
    int steps = 0;
    while (front < rear) {
        int size = rear - front;
        steps++;
        for (int i = 0; i < size; ++i) {
            int cur = queue[front++];
            for (int j = 0; j < coinsSize; ++j) {
                int next = cur - coins[j];
                if (next == 0) {
                    free(queue); free(visited);
                    return steps;
                }
                if (next > 0 && !visited[next]) {
                    visited[next] = 1;
                    queue[rear++] = next;
                }
            }
        }
    }
    free(queue); free(visited);
    return -1;
}