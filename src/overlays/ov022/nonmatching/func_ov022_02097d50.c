/* NONMATCHING: the original contains a dead `orr r1,r1,#0` — a `field |= FLAG`
 * where FLAG is a build-time 0-valued macro from the original header. mwcc
 * constant-folds any literal `| 0` (even through volatile), so the store at
 * +0x468 cannot be reproduced and the function comes out short. Same class as
 * func_ov022_020ad1d0 / func_ov022_020955b0. Semantics below are exact with the
 * always-no-op term omitted. */
extern int func_02030788(void);
extern void func_ov002_0206cd60(int a, int b);
extern void func_ov022_020a35f4(int obj, int a);
extern int data_0204c240;

void func_ov022_02097d50(int arg0, int arg1) {
    *(int *)(arg0 + 0x698) = 0;
    *(int *)(arg0 + 0x69c) = 0x630;
    *(int *)(arg0 + 0x6a0) = 0;
    if (func_02030788() == 0) {
        *(int *)(arg0 + 0x464) |= 0x20;
        /* original also did: *(int *)(arg0 + 0x468) |= <zero-valued flag>; */
    }
    if (arg1 == 0 && (*(unsigned char *)&data_0204c240 & 4) == 0) {
        if ((*(unsigned int *)arg0 & 0x10000) == 0 && *(unsigned char *)(arg0 + 9) == 0)
            func_ov002_0206cd60(1, 3);
    }
    func_ov022_020a35f4(arg0, 1);
}
