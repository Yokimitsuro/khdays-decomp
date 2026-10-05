

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/os.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

fx32 FX_Div(fx32 numer, fx32 denom);
extern const fx16 data_02041210[128 + 1];

/* FX_Atan2 -- NitroSDK fx_atan.c: FX_Atan2. */
fx16 FX_Atan2 (fx32 y, fx32 x)
{
	fx32 a, b, c;
	int sgn;

	if (y > 0) {
		if (x > 0) {
			if (x > y) {
				a = y;
				b = x;
				c = 0;
				sgn = 1;
			} else if (x < y)   {
				a = x;
				b = y;
				c = 6434;
				sgn = 0;
			} else {
				return (fx16)3217;
			}
		} else if (x < 0)   {
			x = -x;
			if (x < y) {
				a = x;
				b = y;
				c = 6434;
				sgn = 1;
			} else if (x > y)   {
				a = y;
				b = x;
				c = 12868;
				sgn = 0;
			} else {
				return (fx16)9651;
			}
		} else {
			return (fx16)6434;
		}
	} else if (y < 0)   {
		y = -y;
		if (x < 0) {
			x = -x;
			if (x > y) {
				a = y;
				b = x;
				c = -12868;
				sgn = 1;
			} else if (x < y)   {
				a = x;
				b = y;
				c = -6434;
				sgn = 0;
			} else {
				return (fx16) - 9651;
			}
		} else if (x > 0)   {
			if (x < y) {
				a = x;
				b = y;
				c = -6434;
				sgn = 1;
			} else if (x > y)   {
				a = y;
				b = x;
				c = 0;
				sgn = 0;
			} else {
				return (fx16) - 3217;
			}
		} else {
			return (fx16) - 6434;
		}
	} else {
		if (x >= 0) {
			return 0;
		} else {
			return (fx16)12868;
		}
	}

	if (b == 0)
		return 0;
	if (sgn)
		return (fx16)(c + data_02041210[FX_Div(a, b) >> 5]);
	else
		return (fx16)(c - data_02041210[FX_Div(a, b) >> 5]);
}
