/* Signed division ABI: quotient in the low word, remainder in the high word. */
extern long long func_02020400(int numerator, int denominator);

/* Encode up to three decimal digits, least-significant digit first.
 * A value of -1 suppresses a leading zero glyph.
 */
void func_ov004_02050634(signed char *digits, int value)
{
    int divisor;
    int digitIndex;
    int suppressLeadingZeros = 1;
    int quotient;

    digits[0] = digits[1] = digits[2] = -1;
    for (divisor = 100, digitIndex = 2; divisor > 0; divisor /= 10, digitIndex--) {
        quotient = (int)func_02020400(value, divisor);
        if (quotient > 0) {
            digits[digitIndex] = quotient;
            suppressLeadingZeros = 0;
            value = (int)(func_02020400(value, divisor) >> 32);
        } else if (!suppressLeadingZeros || digitIndex == 0) {
            digits[digitIndex] = 0;
        }
    }
}

