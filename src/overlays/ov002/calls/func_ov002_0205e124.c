/* Set or clear one column's bit in the mask at +0x4b4 and refresh, but only when
 * the bit is not already in the requested state. func_ov002_0205a730 resolves
 * the id to a bit index (through the stack out-param) and reports its current
 * state, so its return value is compared directly against the requested one.
 * A suppressed panel forces the request to "clear". */
extern int func_ov002_020575d0(void);
extern int func_ov002_0205a730(int *bit, int id);
extern void func_ov002_0205e018(void);

extern char *data_ov002_0207f620;

void func_ov002_0205e124(int id, int on) {
    char *ctx = data_ov002_0207f620;
    int bit;

    if (func_ov002_020575d0() != 0) {
        on = 0;
    }

    {
        int state = func_ov002_0205a730(&bit, id);

        if (state == on) {
            return;
        }
    }

    if (on != 0) {
        *(int *)(ctx + 0x4b4) |= 1 << bit;
    } else {
        *(int *)(ctx + 0x4b4) &= ~(1 << bit);
    }

    func_ov002_0205e018();
}
