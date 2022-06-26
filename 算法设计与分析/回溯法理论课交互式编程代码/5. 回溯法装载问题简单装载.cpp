#include<iostream>
#include<algorithm>
#include <memory.h>
using namespace std;
#define MAXN 20

int w[] = { 5,2,6,4,3 }; //各集装箱重量，从下标0的元素开始
int n = 5, W = 10;
int maxw = 0;		   //存放最优解的总重量
int x[MAXN];		   //存放最优解向量
bool op[MAXN];

void dfs(int i, int tw, int rw) //求解简单装载问题
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
        if (tw + w[i] <= W)			//左孩子结点剪枝
        {
            op[i] = 1;			//选取第i个集装箱
            dfs(i + 1, tw + w[i], rw - w[i]);
        }
        if (tw + rw - w[i] > maxw)		//右孩子结点剪枝
        {
            op[i] = 0;			//不选取第i个集装箱,回溯
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

    printf("Best weight: %d\nSelected objects: ", maxw);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}
