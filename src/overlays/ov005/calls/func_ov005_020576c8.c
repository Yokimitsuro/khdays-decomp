/* When the gate word at +0x4b7c is set, samples the 64-bit timer through func_020031d4 into
 * the pair at +0x4b5c and moves the state word at +0x4b74 to 3.
 *
 * func_020031d4 returns a 64-bit value in r0/r1 -- writing it as one `long long` store is
 * what gives the ROM's two adjacent `str`s. */
extern long long func_020031d4(void);
extern char *data_ov005_0205b810;

void func_ov005_020576c8(void) {
    char *b = data_ov005_0205b810;
    long long t;
    if (*(int *)(b + 0x4b7c) == 0) {
        return;
    }
    t = func_020031d4();
    *(long long *)(b + 0x4b5c) = t;
    *(int *)(b + 0x4b74) = 3;
}
