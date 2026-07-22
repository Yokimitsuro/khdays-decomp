/* When the gate word at +0x4c38 is set, samples the 64-bit timer through func_020031d4 into
 * the pair at +0x4bf4 and moves the state word at +0x4bf0 to 7.
 *
 * func_020031d4 returns a 64-bit value in r0/r1 -- writing it as one `long long` store is
 * what gives the ROM's two adjacent `str`s. */
extern long long func_020031d4(void);
extern char *data_ov005_0205b80c;

void func_ov005_02054a10(void) {
    char *b = data_ov005_0205b80c;
    long long t;
    if (*(int *)(b + 0x4c38) == 0) {
        return;
    }
    t = func_020031d4();
    *(long long *)(b + 0x4bf4) = t;
    *(int *)(b + 0x4bf0) = 7;
}
