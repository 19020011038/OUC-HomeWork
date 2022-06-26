#include<iostream>
#include<algorithm>
#include <memory.h>
using namespace std;
#define MAXN 100

// n种物品,限制重量为W,w[]存放4个物品重量,v[]存放4个物品价值,下标从0开始
int n, W, w[MAXN], v[MAXN];
// 布尔数组op记录第i个物品是否选取
bool op[MAXN];
//d[]将物品递减排序，但不改变w[]和v[]的顺序，只是记录排序后的下标
int d[MAXN];
float p[MAXN]; // p[]为v[] / w[]

//求解结果表示
bool x[MAXN];			//存放最终解
int maxv; 			//存放最优解的总价值

int bound(int i, int tw, int tv)	//求上界
{
    i++;					//从i+1开始
    while (i < n && tw + w[d[i]] <= W)	//若序号为i的物品可以整个放入
    {
        tw += w[d[i]];
        tv += v[d[i]];
        i++;
    }
    if (i < n)
        return tv + (W - tw) * p[d[i]];	//序号为i的物品不能整个放入
    else
        return tv;
}


void dfs(int i, int tw, int tv)
{
    if (i == n)				//找到一个叶子结点
    {
        if (tw <= W && tv > maxv)		//找到一个满足条件的更优解,保存 
        {
            maxv = tv;
            for (int j = 0; j < n; j++)
                x[j] = op[j];
        }
    }
    else					//尚未找完所有物品
    {
        if (tw + w[d[i]] <= W)   //左剪枝
        {
            op[d[i]] = true;				//选取第d[i]个物品
            dfs(i + 1, tw + w[d[i]], tv + v[d[i]]);
        }

        if (bound(i, tw, tv) > maxv)   //右剪枝
        {
            op[d[i]] = false;				//不选取第d[i]个物品,回溯
            dfs(i + 1, tw, tv);
        }

    }
}

int cmp(const int& a, const int& b)
{
    return p[a] > p[b];
}

int main()
{
    // 输入数据
    scanf("%d %d", &n, &W);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &w[i], &v[i]);
        p[i] = (float)v[i] / w[i];
        d[i] = i;
    }

    memset(op, 0, sizeof(op));
    sort(d, d + n, cmp);
    dfs(0, 0, 0);

    printf("Total value: %d\nSelected objects: ", maxv);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}
