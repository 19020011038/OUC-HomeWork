// 排列树
//int x[n];			//x存放解向量，并初始化
//void backtrack(int i)		//求解排列树的递归框架
//{
//    if (i > n)			//搜索到叶子结点,输出一个可行解
//        输出结果;
//    else
//    {
//        for (j = i; j <= n; j++)	//用j枚举i所有可能的选择
//        {
//            …			//第i层的结点选择x[j]的操作
//                swap(x[i], x[j]);	//为保证排列中每个元素不同,通过交换来实现
//            if (constraint(i) && bound(i))
//                backtrack(i + 1);	//满足约束条件和限界函数，进入下一层
//            swap(x[i], x[j]);	//恢复状态
//            …			//第i层的结点选择x[j]的恢复操作
//        }
//    }
//}




// 求全排列
//#include<iostream>
//#include <memory.h>
//using namespace std;
//#define MAXN 20
//
//void swap(int &a, int &b)
//{
//    int temp;
//    temp = a;
//    a = b;
//    b = temp;
//}
//
//void dfs(int a[], int n, int i)
////回溯算法求解向量x
//{
//    if (i >= n)
//    {
//        /*dispasolution(a, n, x);*/
//        for (int i = 0; i < n; i++)
//            cout << a[i] << ' ';
//        cout << endl;
//    }
//
//    else
//    {
//        for (int j = i; j < n; j++)
//        {
//            swap(a[i], a[j]);		//交换a[i]与a[j]
//            dfs(a, n, i + 1);
//            swap(a[i], a[j]);		//交换a[i]与a[j]：恢复
//        }
//    }
//}
//
//int main()
//{
//    int n = 3;
//    int a[] = { 1,2,3 };
//    dfs(a, n, 0);
//    return 0;
//}

