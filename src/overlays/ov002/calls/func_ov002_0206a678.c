/* Scale the Q12 value by the two modifiers the object carries: property 0x56
 * contributes a proportional bonus (0x19a per point) and property 0x57 doubles
 * the result. Rounds up on the way back out of Q12. Values that start at or
 * below zero are returned untouched. */
extern int func_020358f4(void *self, int prop);
extern int func_02005418(int value, int scale);

int func_ov002_0206a678(void *self, int value) {
    int q = value << 0xc;

    if (q > 0) {
        int bonus = func_020358f4(self, 0x56);

        if (bonus > 0) {
            q += func_02005418(q, bonus * 0x19a);
        }
        if (func_020358f4(self, 0x57) != 0) {
            q <<= 1;
        }
        q += 0xfff;
    }

    return q >> 0xc;
}
