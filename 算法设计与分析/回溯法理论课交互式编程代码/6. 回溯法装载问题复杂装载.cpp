#include<iostream>
#include<algorithm>
#include <memory.h>
using namespace std;
#define MAXN 20

int w[] = { 20, 40, 40 }; //各集装箱重量，从下标0的元素开始
int n = 3, c1 = 50, c2 = 50;
int maxw = 0;		   //存放第一艘船最优解的总重量
int x[MAXN];		   //存放第一艘船最优解向量
bool op[MAXN];

void dfs(int i, int tw, int rw) //求第一艘船的解，等价于求解简单装载问题
{
    if (i == n)				//找到一个叶子结点
    {
        if (tw > maxw)
        {
            maxw = tw;			//找到一个满足条件的更优解,保存它
            for (int j = 0; j < n; j++)	//复制最优解
                x[j] = op[j];
        }
    }
    else					//尚未找完所有集装箱
    {
        if (tw + w[i] <= c1)			//左孩子结点剪枝
        {
            op[i] = true;			//选取第i个集装箱
            dfs(i + 1, tw + w[i], rw - w[i]);
        }
        if (tw + rw - w[i] > maxw)		//右孩子结点剪枝
        {
            op[i] = false;			//不选取第i个集装箱,回溯
            dfs(i + 1, tw, rw - w[i]);
        }
    }
}

int main()
{
    memset(op, 0, sizeof(op));

    int rw = 0;
    for (int i = 0; i < n; i++) rw += w[i];
    dfs(0, 0, rw);

    int sum = 0;
    for (int i = 0; i < n; i++) //累计第一艘轮船装完后剩余的集装箱重量
        if (x[i] == false) sum += w[i];
    if (sum <= c2)
    {
        printf("Find a solution. Load No.");
        for (int i = 0; i < n; i++)
            if (x[i]) cout << i + 1 << ' ';
        printf("onto Ship 1 and put the rest onto Ship 2.\n");
    }
    else
    {
        printf("No solution!\n");
    }
}
