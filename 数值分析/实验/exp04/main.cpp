#include <stdio.h>
#include <cmath>

#define MAX_TIMES 100
#define e 0.001
#define ROOT 3.2348365

/// f(x) = 5/6x^4 - 4x^3 + 23/6x^2 + 3x - 17/3
double f(double x) {
    return (5.0 / 6.0) * pow(x, 4) - 4 * pow(x, 3)
            + (23.0 / 6.0) * pow(x, 2) + 3 * pow(x, 1) - (17.0 / 3.0);
}

/// f'(x) = 10/3x^3 - 12x^2 + 23/3x + 3
double f_d(double x) {
    return (10.0 / 3.0) * pow(x, 3) - 12 * pow(x, 2)
            + (23.0 / 3) * pow(x, 1) + 3;
}

void Binary() {
    double left = 2.0;
    double right = 4.0;
    double mid;

    printf("Binary:\n");
    printf("  k\t xk\n");
    for (int i = 1; i <= MAX_TIMES && (right - left) >= e; i++) {
        mid = (left + right) / 2.0;
        if (f(left) * f(mid) < 0) {
            right = mid;
        } else {
            left = mid;
        }
        printf("%3d  %f\n", i, left);
    }
}

void Newton() {
//    double x0 = 2.0;
    double x0 = 3.0;
    double x1;

    printf("Newton:\n");
    printf("  k\t xk\n");
    for (int i = 1; i <= MAX_TIMES; i++) {
        x1 = x0 - f(x0) / f_d(x0);
        printf("%3d  %f\n", i, x1);

        if (fabs(x1 -x0) < e) { // 精度达到要求
            break;
        }
        x0 = x1;
    }
    printf("f(%f) = %f\n", x1, f(x1));
}

int main() {
    Binary();
    Newton();

    return 0;
}