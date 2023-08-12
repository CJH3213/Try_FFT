// FFT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "FFT.h"

// 卷积测试
void ConvolutionTest()
{
    /** 测试范例：
     输入：
        3 7
        1 2 3 4     (4321=1+2x^1+3x^2+4x^3，x=10)
        1 2 3 4 5 6 7 8    (87654321，x=10)
     输出：
        1 4 10 20 30 40 50 60 61 52 32  （系数）
        378754321041  （十进制乘积, x=10）
    */

    //先输入两个多项式次数
    int n, m;
    scanf("%d %d", &n, &m);

    // 输入多项式系数
    Complex F[100], G[100];
    for (int i = 0; i <= n; ++i)
        scanf("%lf", &F[i].r);
    for (int i = 0; i <= m; ++i)
        scanf("%lf", &G[i].r);

    FFT mFFT(n + m);
    mFFT.Conv(F, G);

    for (int i = 0; i <= n + m; ++i)
    {
        printf("%d ", (int)(F[i].r + 0.5));  // 四舍五入
    }
    printf("\n ");

    double sum = 0;
    for (int i = 0; i <= n + m; ++i)
    {
        sum += (int)(F[i].r + 0.5) * pow(10, i);
    }
    printf("%lld ", (uint64_t)sum);
}

int main()
{
    std::cout << "Hello World!\n";

    ConvolutionTest();

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单（黑窗等待关闭）
// 调试程序: F5 或调试 >“开始调试”菜单（黑窗自动关闭）

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
