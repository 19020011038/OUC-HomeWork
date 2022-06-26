#include<iostream>
#include <memory.h>
using namespace std;
#define MAXN 100

// n种物品,限制重量为W,w[]存放4个物品重量,v[]存放4个物品价值,下标从0开始
int n, W, w[MAXN], v[MAXN]; 
// 布尔数组op记录第i个物品是否选取
bool op[MAXN]; 

//求解结果表示
bool x[MAXN];			//存放最终解
int maxv; 			//存放最优解的总价值

void dfs(int i, int tw, int tv)
{

}

int main()
{
    // 输入数据
    scanf("%d %d", &n, &W);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &w[i], &v[i]);

    memset(op, 0, sizeof(op));
    dfs(0, 0, 0);

    printf("Total value: %d\nSelected objects: ", maxv);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}