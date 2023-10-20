#include <complex.h>
#include <math.h>

float log10f(float);
float atan2f(float, float);

float complex
clog10f(float complex z)
{
	float complex w;
	float p, rr;

	rr = cabsf(z);
	p = log10f(rr);
	rr = atan2f(cimagf(z), crealf(z)) * (float) M_IVLN10;
	w = p + rr * I;
	return w;
}
