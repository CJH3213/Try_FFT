#include "FFT.h"
#include <algorithm>

// ������Դ��Bվ@��������@BV1Y7411W73U

// δ�Ż����ٸ���Ҷ�㷨
//void FFT(Complex* a, int lim)
//{
//	if (lim == 1) return;	// ֻ��1��Ԫ��ʱFFT������Ǳ���ֱ�ӷ���
//
//	Complex a0[lim >> 1], a1[lim >> 1];	// ԭ���鰴�±��Ϊ��ż������
//	for (int i = 0; i < lim, i += 2)
//		a0[i >> 1] = a[i], a1[i >> 1] = a[i + 1];
//
//	FFT(a0, lim >> 1);	// �ֱ����ż������ �ݹ� FFT
//	FFT(a1, lim >> 1);
//
//	Complex wn = Complex(cos(2.0 * PI / lim), sin(2.0 * PI / lim));	// ��n�ε�λ��
//	Complex w = Complex(1, 0);	//��ת����
//
//	for (int k = 0; k < (lim >> 1); ++k)	// �ϲ���ż��������ԭ����
//	{	// ����������ǰ��һ��ͬʱ���кϲ�
//		a[k] = a0[k] + w * a1[k];	// �ϲ�ԭ����ǰһ��
//		a[k + (lim >> 1)] = a0[k] - w * a1[k];	//�ϲ�ԭ�����һ��
//		w = w * wn;	// ��ת���Ӵ�������
//	}
//}

FFT::FFT(int n)
{
	// n��a�����ԭ����
	// lim�Ǵ�����
	// ������8�����ݣ�lim=1000��len=4
	lim = 1;
	len = 0;
	while (lim <= n)
		lim <<= 1, len++;

	// Ԥ����rav����
	rev[0] = 0;
	for (int i = 0; i < lim; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
}

void FFT::FFT_Handle(Complex* a, int opt)
{
	// ��ԭ�����������
	for (int i = 0; i < lim; ++i)
		if (i < rev[i])	// ��ֹ�ظ�����
			std::swap(a[i], a[rev[i]]);

	// ���ϲ����� = log(lim)����ǰ����dep
	//for (int dep = 1; dep <= log2(lim); ++dep)
	//{
	//	int m = 1 << dep;		//�ϲ������г��� = 2 ^ dep
	// ���µ�m��֮ǰ�汾Сһ������ʡ��m/2
	for(int m = 1; m < lim; m <<=1)
	{
		Complex wn = Complex(cos(PI / m),opt * sin(PI / m));	//��m�ε�λ��

		for (int k = 0; k < lim; k += (m<<1))	// ÿ��m��Ϊһ�飬��������
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
	// ����FFTʵ�ֿ��پ����a x b = IDFT(DFT(a) * DFT(b))

	FFT_Handle(a, 1);
	FFT_Handle(b, 1);

	// ��FFT����������
	for (int i = 0; i < lim; ++i)
		a[i] = a[i] * b[i];

	FFT_Handle(a, -1);
	// ���������a����
}
