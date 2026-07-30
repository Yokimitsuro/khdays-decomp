/* Renders a value, clamped to 9999, as up to four decimal digit tiles.
 * Leading zeroes stay blank, but the ones place is always drawn. */
extern unsigned long long func_02020400(int value, int divisor);

typedef struct Ov003TileCell {
    unsigned short value;
} Ov003TileCell;

static inline unsigned short Ov003_MakeDigitTile(int digit)
{
    return (digit + 0x34) | 0x9000;
}

void func_ov003_0204d1c0(Ov003TileCell *dst, unsigned int value)
{
    int divisor;
    int leading;

    leading = 1;
    if (value > 9999) {
        value = 9999;
    }
    divisor = 1000;
    do {
        unsigned long long q = func_02020400(value, divisor);
        int d = (char)q;

        if (d == 0) {
            goto zero_digit;
        }
        leading = 0;
        dst->value = Ov003_MakeDigitTile(d);
        goto next_digit;
zero_digit:
        if (leading == 0 || divisor == 1) {
            dst->value = Ov003_MakeDigitTile(d);
        }
next_digit:
        {
            unsigned long long q2 = func_02020400(value, divisor);
            value = (unsigned short)(q2 >> 0x20);
        }
        dst = dst + 1;
        divisor = divisor / 10;
    } while (divisor > 0);
}
