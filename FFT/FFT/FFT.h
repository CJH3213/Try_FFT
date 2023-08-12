#pragma once
#include <math.h>
#include "Complex.h"

const double PI = acos(-1);
const int maxn = 2000;

class FFT
{
public:
	int rev[maxn], len, lim;

	FFT(int n);

	void FFT_Handle(Complex* a, int opt);
	void Conv(Complex* a, Complex* b);
};

