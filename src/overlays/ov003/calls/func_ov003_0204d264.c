/* Renders a value, clamped to 999, as up to three decimal digit tiles.
 * Leading zeroes stay blank, but the ones place is always drawn. */
extern unsigned long long func_02020400(int value, int divisor);

typedef struct Ov003TileCell {
    unsigned short value;
} Ov003TileCell;

static inline unsigned short Ov003_MakePaletteDigitTile(unsigned int palsh, int digit)
{
    return (digit + 0x34) | (palsh >> 16);
}

void func_ov003_0204d264(Ov003TileCell *dst, unsigned int value, int pal)
{
    unsigned int palsh;
    int zero;
    int divisor;
    int leading;
    unsigned long long quotient;
    int digit;

    palsh = pal << 0x1c;
    leading = 1;
    if (value > 999) {
        value = 999;
        divisor = 100;
        zero = 0;
    } else {
        divisor = 100;
        zero = 0;
    }
    do {
        quotient = func_02020400(value, divisor);
        digit = (char)quotient;
        if (digit != 0) {
            leading = zero;
            dst->value = Ov003_MakePaletteDigitTile(palsh, digit);
        } else if (leading == 0 || divisor == 1) {
            dst->value = Ov003_MakePaletteDigitTile(palsh, digit);
        }
        quotient = func_02020400(value, divisor);
        value = (unsigned short)(quotient >> 0x20);
        dst = dst + 1;
        divisor = divisor / 10;
    } while (divisor > 0);
}
