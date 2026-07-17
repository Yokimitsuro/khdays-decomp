/*
 * Apply a mode change to the actor (x4: ov045/064/082/099).
 *
 * Entering 0x2e re-inits (020b48b4); 0x2f and 0x30 share an arm that rebinds the block at
 * self+0x2df0 (020b41c8). Both no-op when the mode did not change (+0x6bc caches it). Then
 * 020a384c hands the mode down and the UI band gets it translated (020519b0 -> 02052024) at/above
 * 0x2e, or straight (020521a4) below.
 *
 * Off the ov034/ov046 template, plus one thing worth its own line: the ROM's `cmp r4, r1` says
 * the guard is written `mode != *(int *)(self + 0x6bc)` -- the MODE first. Written the other way
 * round (which is how the rest of this family spells it) mwcc emits `cmp r1, r4` and nothing
 * else changes: same size, same registers, two bytes different. Ghidra had it right here and I
 * still normalised it away out of habit; when a diff is two reversed compares and nothing else,
 * read the operand order off the disassembly rather than trusting the family's usual spelling.
 */
extern void func_ov045_020b48b4(int self);
extern void func_ov045_020b41c8(int self, char *p);
extern void func_ov022_020a384c(int self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov045_020b3684(int self, int mode) {
    int flag;
    int ret;

    switch (mode) {
    case 0x2e:
        if (mode != *(int *)(self + 0x6bc)) { func_ov045_020b48b4(self); }
        break;
    case 0x2f:
    case 0x30:
        if (mode != *(int *)(self + 0x6bc)) {
            func_ov045_020b41c8(self, (char *)(self + 0x2df0));
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    flag = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }
    ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
    if (mode >= 0x2e) {
        func_ov002_02052024((void *)(self + 0xda8), self + 0x2d38, mode, 2, ret);
        return;
    }
    func_ov002_020521a4((void *)(self + 0xda8), self + 0x2d38, mode, flag);
}
