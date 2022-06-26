#include <iostream>
#include <cmath>
#define MAXN 1001
#define MAXINT 2147483647

int n;
int a[MAXN], b[MAXN]; //输入数据
int f1, f2[MAXN];	//流水线作业总时间
int x[MAXN];		//临时解
int bestx[MAXN];	//最优解
int bestf;	//最优解的成本

void swap(int& a, int& b) { int temp; temp = a; a = b; b = temp; }

void dfs(int i)			//从第i层开始搜索
{
    if (i > n)				//到达叶结点,产生一种调度方案
    {
        if (f2[n] < bestf)		//找到更优解
        {
            bestf = f2[n];
            for (int j = 1; j <= n; j++)	//复制解向量
                bestx[j] = x[j];
        }
    }
    else
    {
        for (int j = i; j <= n; j++)		//没有到达叶结点,考虑可能的作业
        {
            swap(x[i], x[j]);
            f1 += a[x[i]];		//选择作业x[i],在M1上执行完的时间
            f2[i] = std::max(f1, f2[i - 1]) + b[x[i]];
            if (f2[i] < bestf)		//剪枝
                dfs(i + 1);
            f1 -= a[x[i]];		//回溯
            swap(x[i], x[j]);
        }
    }
}


int main()
{
    while (scanf("%d", &n), n != 0)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d %d", &a[i], &b[i]);
            x[i] = i;
        }
        f1 = 0; bestf = MAXINT;
        dfs(1);
        printf("Total time: %d\nTasks order: ", bestf);
        for (int i = 1; i <= n; i++) std::cout << bestx[i] << ' ';
        printf("\n");
    }
    return 0;
}