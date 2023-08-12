#pragma once

struct Complex
{
	double r, i;

	Complex() { r = 0, i = 0; }
	Complex(double real, double imag):r(real),i(imag){}
};

inline Complex operator + (Complex a, Complex b)
{
	return Complex(a.r + b.r, a.i + b.i);
}

inline Complex operator - (Complex a, Complex b)
{
	return Complex(a.r - b.r, a.i - b.i);
}

inline Complex operator * (Complex a, Complex b)
{
	return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i *b.r);
}