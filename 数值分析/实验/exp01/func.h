//
// Created by lenovo on 2020/3/12.
//

#ifndef EXP1_FUNC_H
#define EXP1_FUNC_H

/**
 * 用拉格朗日插值算法拟合值
 * @param x0 已知结点的x坐标
 * @param y0 已知结点的y坐标
 * @param n 已知结点数量
 * @param x 要求的点的x坐标
 *@return 
 */
double lagrange(const double x0[], const double y0[], int n, double x){
    double ans = 0;//保存结果
    double temp = 1;//保存基函数

    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; ++j) {
            if(j != i){
                temp = temp * (x - x0[j]) / (x0[i] - x0[j]);//基函数计算
            }
        }
        ans += y0[i] * temp;//基函数与f(x)值的乘积求和
        temp = 1;//归1继续计算下一个基函数
    }
    return ans;
}

/**
 * 利用差商性质1计算差商
 * @param x0 已知结点x坐标
 * @param y0 已知结点y坐标
 * @param n 要求差商的次数
 * @return n次差商
 */
double differenceQuo(const double x0[], const double y0[], int n){
    double ans = 0;
    double temp = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j != i){
                temp *= 1 / (x0[i] - x0[j]);
            }
        }
        temp *= y0[i];
        ans += temp;
        temp = 1;
    }
    
    return ans;
}

/**
 * 用牛顿插值法计算某一点的函数估计值
 * @param x0 已知结点x坐标
 * @param y0 已知结点y坐标
 * @param n 已知结点数量
 * @param x 要求的点的x坐标
 * @return
 */
double newton(const double x0[], const double y0[], int n, double x){
    double ans = 0;//保存计算结果
    double temp = 1;//保存牛顿插值中的每一项

    for (int i = 0; i < n; ++i) {
        for(int j = 0;j < i; ++j){
            temp *= (x - x0[j]);
        }
        temp *= differenceQuo(x0,y0,i + 1);//与差商相乘
        ans += temp;//求和
        temp = 1;//归1进行下一轮计算
    }
    return ans;
}

#endif //EXP1_FUNC_H
