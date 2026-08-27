/* Ov002_CountDigits - how many decimal digits a number needs.
 *
 * The sign is dropped first, so -5 and 5 both need one, and zero needs one
 * rather than none because the count is taken after the first divide.
 *
 * ARM, leaf, no relocations: the divide-by-ten magic sits in the function's own
 * literal pool.
 */
int func_ov002_02059810(int nValue)
{
    int nDigits;

    nDigits = 0;
    if (nValue < 0) {
        nValue = -nValue;
    }
    do {
        nValue = nValue / 10;
        nDigits++;
    } while (nValue > 0);
    return nDigits;
}
