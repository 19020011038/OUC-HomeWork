#include <iostream>
#define MAXN 20
#define MAXINT 2147483647

int n = 4;
int c[MAXN][MAXN] = { {0},{0,9,2,7,8},{0,6,4,3,7},
                   {0,5,8,1,8},{0,7,6,9,4} };
//下标0的元素不用，c[i][j]表示第i个人执行第j个任务的成本

int x[MAXN];		//临时解
int cost = 0;		//临时解的成本
int bestx[MAXN];	//最优解
int mincost = MAXINT;	//最优解的成本

void swap(int& a, int& b) { int temp; temp = a; a = b; b = temp; }

void dfs(int i)			//用解空间树为排列树的方法求解
{
    if (i > n)				//到达叶子结点
    {
        cost = 0;  //求cost
        for (int j = 1; j <= n; j++) cost += c[j][x[j]];
        if (cost < mincost)		//比较求最优解
        {
            mincost = cost;
            for (int j = 1; j <= n; j++)
                bestx[j] = x[j];
        }
    }
    else
    {
        for (int j = i; j <= n; j++)		//试探人员i与j交换任务
        {
            swap(x[i], x[j]);
            dfs(i + 1);
            swap(x[i], x[j]);  // 回溯
        }
    }
}

int main()
{
    for (int i = 1; i <= n; i++) x[i] = i;
    dfs(1);
    printf("Total cost: %d\nTasks order: ", mincost);
    for (int i = 1; i <= n; i++) std::cout << bestx[i] << ' ';
	return 0;
}