/* Hands the actor's panel over to the shared UI, unless the run forbids it.
 *
 * In mission mode (flag 4) the name is always shown. Otherwise it is shown
 * when story flag 0x2089 is set, or when the member's head byte is '0'.
 * Story flag 0x208b suppresses the whole handover.
 *
 * The mission-mode arm is written first because the original tests the flag
 * and branches into the member path, and the mission arm borrows its value
 * from the suppression flag rather than materialising another 1.
 */
extern int func_02023588(int flag);
extern void func_ov022_0209fb60(int a, int b, int c);
extern void func_ov002_02051d6c(int a, int b, int c);
extern void func_ov002_02051eec(int a, int b, int c, int d, int e);
extern int data_ov030_020b5a00;
extern unsigned char data_0204c240;
extern int data_0204c678;

void func_ov030_020b35dc(int self) {
    int base = *(int *)&data_ov030_020b5a00;
    int ok = 1;
    int named;

    if ((data_0204c240 & 4) != 0) {
        named = ok;
    } else {
        int member = (int)&data_0204c678
                     + *(unsigned char *)(self + 9) * 0x104;
        if (func_02023588(0x2089) != 0
            || *(unsigned char *)(member + 4) == 0x30) {
            named = 1;
        } else {
            named = 0;
        }
        if (func_02023588(0x208b) != 0) {
            ok = 0;
        }
    }

    if (ok != 0) {
        func_ov022_0209fb60(base, 1, 2);
        if (named != 0 && *(signed char *)(base + 0xf0d) != 0) {
            *(unsigned char *)(base + 0xf0c) |= 1;
        }
        func_ov002_02051d6c(base + 0xf0c, base + 0x2c54, self + 0x910);
        func_ov002_02051eec(self + 0xf0c, base + 0x2c54,
                            *(int *)(self + 0x2bd0),
                            *(unsigned char *)(self + 9), 0x78);
    }
}
