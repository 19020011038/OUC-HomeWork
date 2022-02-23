#include <stdio.h>
#include <cmath>

#define REAL_VALUE 0.785398

/// 被积函数 f(x)
double func(double x) {
    return sqrt(2 * x - x * x);
}

double T[20];
double S[20];
double C[20];
double R[20];
int k = 4;

/// 二分点的函数值之和
double sum(double a, double b, double h) {
    double result = 0.0;

    double x = a;
    while (x < b) {
        result += func(x + h / 2);
        x += h;
    }

    return result;
}

/// 龙贝格算法
void Romberg() {
    double a = 0.0;
    double b = 1.0;

    double h = b - a;
    T[1] = h / 2.0 * (func(a) + func(b));

    T[2] = T[1] / 2.0 + h / 2.0 * sum(a, b, h);
    h = h / 2.0;
    T[3] = T[2] / 2.0 + h / 2.0 * sum(a, b, h);
    h = h / 2.0;
    T[4] = T[3] / 2.0 + h / 2.0 * sum(a, b, h);
    h = h / 2.0;

    S[1] = T[2] + (T[2] - T[1]) / 3;
    S[2] = T[3] + (T[3] - T[2]) / 3;
    S[3] = T[4] + (T[4] - T[3]) / 3;

    C[1] = S[2] + (S[2] - S[1]) / 15;
    C[2] = S[3] + (S[3] - S[2]) / 15;

    R[1] = C[2] + (C[2] - C[1]) / 63;

    while (fabs(R[k - 3] - REAL_VALUE) >= 0.0000005) {
        k++;
        T[k] = T[k - 1] / 2.0 + h / 2.0 * sum(a, b, h);
        h = h / 2;
        S[k - 1] = T[k] + (T[k] - T[k - 1]) / 3;
        C[k - 2] = S[k - 1] + (S[k - 1] - S[k - 2]) / 15;
        R[k - 3] = C[k - 2] + (C[k - 2] - C[k - 3]) / 63;
    }
}

int main() {

    Romberg();
    /// 验证龙贝格公式的积分效果
    printf("i\t R[i]\t\t 误差\n");
    for (int i = 1; i < k - 2; i++) {
        printf("%d\t %f\t %f\n", i, R[i], fabs(R[i] - REAL_VALUE));
    }

    ///验证龙贝格公式对复合梯形公式精度的提高
    printf("k\t T[k]\t\t S[k]\t\t C[k]\t\t R[k]\n");
    for (int i = 1; i < k + 1; i++) {
        if (i < 2) {
            printf("%d\t %f\n", i, T[i]);
        } else if (i < 3) {
            printf("%d\t %f\t %f\n", i, T[i], S[i - 1]);
        } else if (i < 4) {
            printf("%d\t %f\t %f\t %f\t\n", i, T[i], S[i - 1], C[i - 2]);
        } else {
            printf("%d\t %f\t %f\t %f\t %f\n", i, T[i], S[i - 1], C[i - 2], R[i - 3]);
        }
    }

    return 0;
}


