// 写不出来
#include <stdbool.h>
#include <stdlib.h>

void dfs(int **prerequisites, int row, int col, int rowmax, bool *visited)
{
    if (row < 0 || row >= rowmax || visited[prerequisites[row][0]] == true)
    {
        return;
    }
    visited[prerequisites[row][col]] == true;
    if (col == 0)
        dfs(prerequisites, row, 1, rowmax, visited);
}
bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize)
{
    int cnt = 0;
    bool *visited = (bool *)calloc(numCourses, sizeof(bool));
    for (int i = 0; i < prerequisitesSize; i++)
    {
        dfs(prerequisites, i, 0, prerequisitesSize, visited);
    }
    for (int i = 0; i < numCourses; i++)
    {
    }
}