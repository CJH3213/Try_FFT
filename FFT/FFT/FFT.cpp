#include "FFT.h"
#include <algorithm>

// 代码来源：B站@鹤翔万里@BV1Y7411W73U

// 未优化快速傅里叶算法
//void FFT(Complex* a, int lim)
//{
//	if (lim == 1) return;	// 只有1个元素时FFT结果还是本身，直接返回
//
//	Complex a0[lim >> 1], a1[lim >> 1];	// 原数组按下标分为奇偶两数组
//	for (int i = 0; i < lim, i += 2)
//		a0[i >> 1] = a[i], a1[i >> 1] = a[i + 1];
//
//	FFT(a0, lim >> 1);	// 分别对奇偶两数组 递归 FFT
//	FFT(a1, lim >> 1);
//
//	Complex wn = Complex(cos(2.0 * PI / lim), sin(2.0 * PI / lim));	// 主n次单位根
//	Complex w = Complex(1, 0);	//旋转因子
//
//	for (int k = 0; k < (lim >> 1); ++k)	// 合并奇偶数组结果到原数组
//	{	// 蝴蝶操作：前后一半同时进行合并
//		a[k] = a0[k] + w * a1[k];	// 合并原数组前一半
//		a[k + (lim >> 1)] = a0[k] - w * a1[k];	//合并原数组后一半
//		w = w * wn;	// 旋转因子次数增加
//	}
//}

FFT::FFT(int n)
{
	// n是a数组的原长度
	// lim是次数界
	// 如输入8个数据，lim=1000，len=4
	lim = 1;
	len = 0;
	while (lim <= n)
		lim <<= 1, len++;

	// 预处理rav数组
	rev[0] = 0;
	for (int i = 0; i < lim; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

void FFT::FFT_Handle(Complex* a, int opt)
{
	// 对原数组进行排序
	for (int i = 0; i < lim; ++i)
		if (i < rev[i])	// 防止重复调换
			std::swap(a[i], a[rev[i]]);

	// 最大合并层数 = log(lim)，当前层数dep
	//for (int dep = 1; dep <= log2(lim); ++dep)
	//{
	//	int m = 1 << dep;		//合并后序列长度 = 2 ^ dep
	// 以下的m比之前版本小一倍，以省略m/2
	for(int m = 1; m < lim; m <<=1)
	{
		Complex wn = Complex(cos(PI / m),opt * sin(PI / m));	//主m次单位根

		for (int k = 0; k < lim; k += (m<<1))	// 每隔m个为一组，蝴蝶操作
		{
			Complex w = Complex(1, 0);

			for (int j = 0; j < m; ++j)
			{
				Complex u = a[k + j];
				Complex t = w * a[k + j + m];
				a[k + j] = u + t;
				a[k + j + m] = u - t;
				w = w * wn;
			}
		}
	}

	if (opt == -1)
		for (int i = 0; i < lim; ++i)
			a[i].r /= lim;
}

void FFT::Conv(Complex* a, Complex* b)
{
	// 利用FFT实现快速卷积：a x b = IDFT(DFT(a) * DFT(b))

	FFT_Handle(a, 1);
	FFT_Handle(b, 1);

	// 将FFT结果逐项相乘
	for (int i = 0; i < lim; ++i)
		a[i] = a[i] * b[i];

	FFT_Handle(a, -1);
	// 结果保存在a数组
}
