/* Turn the roster highlight on or off for every row, and remember which it is.
 *
 * The row count comes from the roster module, plus one more row while the phase word reads five.
 * Every row is prepared and then set to the same state, and the state is finally recorded as bit 1
 * of the flag byte at 0x1b5 of the owner.
 *
 * The loop is written with labels rather than a while or a for, and that is deliberate. This
 * compiler duplicates a loop condition that contains calls, emitting it once before the loop and
 * once at the bottom, which is twenty four bytes more than the original; and a while(1) with a
 * leading break puts the test at the top instead of entering at it. Both parts of the bound also
 * need their own locals, or the single add takes its operands the other way round.
 */

typedef unsigned char u8;

extern int func_ov002_0206b78c(void);
extern int func_ov022_020882f8(void);
extern void func_01fffde0(int index);
extern void func_ov022_020888ec(int index, int on);

void func_ov002_0207b078(char *self, int unused, int on) {
    int i = 0;

    goto check;
loop:
    func_01fffde0(i);
    func_ov022_020888ec(i, on);
    i++;
check:
    {
        int extra = (func_ov002_0206b78c() == 5);

        int total = func_ov022_020882f8();

        if (i < total + extra) {
            goto loop;
        }
    }
    if (on != 0) {
        *(u8 *)(self + 0x1b5) |= 2;
    } else {
        *(u8 *)(self + 0x1b5) &= ~2;
    }
}
