/* Step the ov008 list cursor by `step` slots and return the first slot the scroll widget
 * accepts. Starting from the current slot byte at +0x54, it offers up to 12 candidates,
 * each wrapped into [0,11] by `(cell + 12) % 12`, to the widget via func_ov025_0208dc8c and
 * asks func_ov025_0208dc74 whether the pick took. The first accepted slot is returned; if
 * all twelve are refused the cursor stays where it was.
 *
 * Two things had to be right for this to match, and the previous NONMATCHING note blamed the
 * compiler for both:
 *   - func_ov025_0208dc8c takes ONE argument. The ROM's r1 and r2 at the call are not
 *     arguments at all: r1 is the dead high half of the `smull` that multiplies the quotient
 *     back for the modulo, and r2 is the live `x`. Declaring four parameters made mwcc
 *     compute and reload them, and made the `smull` look unreproducible.
 *   - the walking cell and the wrapped remainder are the SAME variable (both in r7), and `i`
 *     must be declared BEFORE it so the two land in r6/r7 the way the ROM has them. */
extern void func_ov025_0208dc8c(int slot);
extern unsigned short func_ov025_0208dc74(void);

unsigned int func_ov025_020a5284(int param_1, int param_2) {
    int i = 0;
    int cell = *(unsigned char *)(param_1 + 0x54) + param_2;
    do {
        int x = cell + 0xc;
        cell = x % 12;
        func_ov025_0208dc8c(cell & 0xffff);
        if (func_ov025_0208dc74() != 0) {
            return cell;
        }
        cell = cell + param_2;
        i++;
    } while (i < 0xc);
    return *(unsigned char *)(param_1 + 0x54);
}
