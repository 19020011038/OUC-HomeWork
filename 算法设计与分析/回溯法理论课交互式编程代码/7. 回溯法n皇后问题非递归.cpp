#include<iostream>
#include <cmath>
#define MAXN 20

int q[MAXN], ret = 0;

void dispasolution(int n)
{
    printf("Solution #%d:\n", ++ret);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < q[i]; j++) printf(". ");
        printf("o ");
        for (int j = q[i] + 1; j <= n; j++) printf(". ");
        printf("\n");
    }
}

bool place(int i)	//测试第i行的q[i]列上能否摆放皇后
{
    int j = 1;
    if (i == 1) return true;
    while (j < i)			//j=1～i-1是已放置了皇后的行
    {
        if ((q[j] == q[i]) || (std::abs(q[j] - q[i]) == abs(j - i)))
            //该皇后是否与以前皇后同列，位置(j,q[j])与(i,q[i])是否同对角线
            return false;
        j++;
    }
    return true;
}

void Queens(int n)	//求解n皇后问题
{
    int i = 1;		//i表示当前行,也表示放置第i个皇后
    q[i] = 0;		//q[i]是当前列,每个新考虑的皇后初始位置置为0列
    while (i >= 1)	//尚未回溯到头，循环
    {
        q[i]++;		//原位置后移动一列
        while (q[i] <= n && !place(i))  //试探一个位置(i,q[i])
            q[i]++;
        if (q[i] <= n)	//为第i个皇后找到了一个合适位置(i,q[i])
        {
            if (i == n)	//若放置了所有皇后,输出一个解
                dispasolution(n);
            else		//皇后没有放置完
            {
                i++;	//转向下一行,即开始下一个新皇后的放置
                q[i] = 0;	//每个新考虑的皇后初始位置置为0列
            }
        }
        else i--; 	//若第i个皇后找不到合适的位置,则回溯到上一个皇后
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    Queens(n);
    return 0;
}