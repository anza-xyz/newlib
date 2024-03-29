
/* @(#)w_scalb.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * wrapper scalb(double x, double fn) is provide for
 * passing various standard test suite. One
 * should use scalbn() instead.
 */

#include "fdlibm.h"
#include <errno.h>

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
#ifdef _SCALB_INT
	double scalb(double x, int fn)		/* wrapper scalb */
#else
	double scalb(double x, double fn)	/* wrapper scalb */
#endif
#else
	double scalb(x,fn)			/* wrapper scalb */
#ifdef _SCALB_INT
	double x; int fn;
#else
	double x,fn;
#endif
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_scalb(x,fn);
#else
	double z;
	z = __ieee754_scalb(x,fn);
	if(_LIB_VERSION == _IEEE_) return z;
	if(!(finite(z)||isnan(z))&&finite(x)) {
	    /* scalb overflow */
#ifndef _REENT_ONLY
	    errno = ERANGE;
#endif /* _REENT_ONLY */
	    return (x > 0.0 ? HUGE_VAL : -HUGE_VAL);
	}
	if(z==0.0&&z!=x) {
	    /* scalb underflow */
#ifndef _REENT_ONLY
	    errno = ERANGE;
#endif /* _REENT_ONLY */
	    return copysign(0.0,x);
	}
#ifndef _SCALB_INT
	if(!finite(fn)) {
#ifndef _REENT_ONLY
	    errno = ERANGE;
#endif /* _REENT_ONLY */
	}
#endif
	return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
