typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef s32 fx32;
typedef s16 fx16;
fx32 FX_Inv(fx32 numer, fx32 denom);
extern const fx16 data_02041210[128 + 1];

/* func_020050b4 -- NitroSystem fx_atan.c: FX_Atan2. */
fx16 func_020050b4 (fx32 y, fx32 x)
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
		return (fx16)(c + data_02041210[FX_Inv(a, b) >> 5]);
	else
		return (fx16)(c - data_02041210[FX_Inv(a, b) >> 5]);
}
