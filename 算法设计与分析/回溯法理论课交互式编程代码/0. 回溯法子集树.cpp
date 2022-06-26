// 子集树
//int x[n];			   //x存放解向量，全局变量
//void backtrack(int i)		   //求解子集树的递归框架
//{
//    if (i > n)			   //搜索到叶子结点,输出一个可行解
//        输出结果;
//    else
//    {
//        for (j = 下界; j <= 上界; j++)   //用j枚举i所有可能的选择
//        {
//            x[i] = j;		   //产生一个可能的解分量
//            …			   //其他操作
//                if (constraint(i) && bound(i))
//                    backtrack(i + 1);	   //满足约束条件和限界函数,继续下一层
//        }
//    }
//}



// 求幂集
//#include<iostream>
//#include <memory.h>
//using namespace std;
//#define MAXN 20
//
//void dfs(int a[], int n, int i, bool x[])
////回溯算法求解向量x
//{
//    if (i >= n)
//    {
//        /*dispasolution(a, n, x);*/
//        for (int i = 0; i < n; i++)
//            if (x[i]) cout << a[i] << ' ';
//        cout << endl;
//    }
//
//    else
//    {
//        x[i] = false; dfs(a, n, i + 1, x);		//不选择a[i]
//        x[i] = true; dfs(a, n, i + 1, x);		//选择a[i]
//    }
//}
//
//int main()
//{
//    int n = 3;
//    int a[] = { 1,2,3 };
//    bool x[MAXN];
//    memset(x, 0, sizeof(x));
//    dfs(a, n, 0, x);
//    return 0;
//}

