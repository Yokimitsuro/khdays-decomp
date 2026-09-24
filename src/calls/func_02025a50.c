#pragma thumb on
/* func_02025a50 -- format a 64-bit fixed-point value as two wide strings: the decimal integer part
 * into pIntOut and the fraction digits (to `precision` places) into pFracOut, both zero-terminated,
 * through the byte formatter func_020258fc. */
typedef unsigned short u16;
typedef long long s64;

extern void func_020258fc(s64 value, int precision, char *pIntText, char *pFracText);

static inline void WidenText(u16 *pDst, const char *pSrc)
{
    while (*pSrc != 0) {
        *pDst++ = *pSrc++;
    }
    *pDst = 0;
}

void func_02025a50(s64 value, int precision, u16 *pIntOut, u16 *pFracOut)
{
    char aIntText[26];
    char aFracText[14];

    func_020258fc(value, precision, aIntText, aFracText);
    WidenText(pIntOut, aIntText);
    WidenText(pFracOut, aFracText);
}
