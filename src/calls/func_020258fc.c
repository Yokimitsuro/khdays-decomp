#pragma thumb on
/* func_020258fc -- format a 64-bit 20.12 fixed-point value as decimal text: the integer part into
 * pIntText (at least "0"; a 32-bit fast path when it fits) and, when `precision` > 0, the fraction
 * as eight digits (the three nibbles scaled by 1e8 and summed, 1e8 added so leading zeros survive)
 * cut to `precision` characters into pFracText, which is first filled with '0'. */
typedef unsigned int u32;
typedef long long s64;

extern s64 func_020201b8(s64 numerator, s64 denom);   /* 64-bit signed divide */
extern void MI_CpuFill8(void *dest, unsigned char data, u32 size);

static inline void ReverseText(char *pText, int nLen)
{
    char *pHead;
    char *pTail;

    pText[nLen] = 0;
    if (nLen >= 2) {
        for (pHead = pText, pTail = pText + nLen - 1; pHead < pTail; pHead++, pTail--) {
            char c = *pHead;
            *pHead = *pTail;
            *pTail = c;
        }
    }
}

void func_020258fc(s64 value, int precision, char *pIntText, char *pFracText)
{
    s64 ipart = value >> 12;
    u32 frac = (u32)value & 0xfff;
    int len = 0;

    if ((ipart >> 32) == 0) {
        u32 n = (u32)ipart;

        while (n != 0) {
            u32 q = n / 10;

            pIntText[len] = (char)(n - q * 10 + '0');
            n = q;
            len++;
        }
    } else {
        while (ipart != 0) {
            s64 q = func_020201b8(ipart, 10);

            pIntText[len] = (char)((int)(ipart - q * 10) + '0');
            ipart = q;
            len++;
        }
    }
    if (len == 0) {
        pIntText[len] = '0';
        len++;
    }
    ReverseText(pIntText, len);

    if (precision > 0) {
        u32 n;
        int i;

        MI_CpuFill8(pFracText, '0', 13);
        n = ((frac & 0xf) * 100000000 >> 12) +
            ((((frac & 0xf00) >> 8) * 100000000 >> 4) + (((frac & 0xf0) >> 4) * 100000000 >> 8)) +
            100000000;
        for (i = 0; i < 8; i++) {
            u32 q = n / 10;

            pFracText[i] = (char)(n - q * 10 + '0');
            n = q;
        }
        pFracText[i] = 0;
        if (i >= 2) {
            char *pHead;
            char *pTail;

            for (pHead = pFracText, pTail = pFracText + i - 1; pHead < pTail; pHead++, pTail--) {
                char c = *pHead;
                *pHead = *pTail;
                *pTail = c;
            }
        }
    }
    pFracText[precision] = 0;
}
