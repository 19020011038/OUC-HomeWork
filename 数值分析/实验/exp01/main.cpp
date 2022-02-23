#include <iostream>
#include <fstream>
#include <cmath>
#include "func.h"

using namespace std;

int main() {
    double x0[100], y0[100];
    int num;
    double x[1000],y[1000];
//    x0[0] = -4;
//    y0[0] = sin(-4);
//    x0[1] = -2;
//    y0[1] = sin(-2);
//    x0[2] = 0;
//    y0[2] = sin(0);
//    x0[3] = 2;
//    y0[3] = sin(2);
//    x0[4] = 4;
//    y0[4] = sin(4);
    x0[0] = -4;
    y0[0] = pow(2,-4);
    x0[1] = -2;
    y0[1] = pow(2,-2);
    x0[2] = 0;
    y0[2] = pow(2,0);
    x0[3] = 2;
    y0[3] = pow(2,2);
    x0[4] = 4;
    y0[4] = pow(2,4);
    for (int i = 0; i < 100; ++i) {
        x[i] = 5 - 0.1 * i;
        y[i] = newton(x0,y0,5,x[i]);
    }

//    cout << "请输入数据点总数：" << endl;
//    cin >> num;
//    for (int i = 0; i < num; ++i) {
//        cout << "请输入第" << i + 1 << "个数据点 x y" << endl;
//        cin >> x0[i] >> y0[i];
//    }
    ofstream oFile;

    //打开要输出的文件
    oFile.open("resultsheet.csv", ios::out | ios::trunc);
    for (int j = 0; j < 100; ++j) {
        oFile << x[j] << "," << y[j] << endl;
    }

    //oFile << "张三" << "," << "22" << "," << "1" << "," << "JIM" << endl;
    //oFile << "李四" << "," << "23" << "," << "3" << "," << "TOM" << endl;

    oFile.close();
    return 0;
}