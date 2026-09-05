/* Drives the ov038 charge sequence. Instruction-for-instruction the same
 * routine as the matched ov084 driver on a different block layout: the
 * state/timer pair lives at +0 and +0x10c, the emitter at +4, and each of the
 * two transitions also rebinds the scene's default animations and re-arms the
 * sequence block at +0x118 of it.
 *
 * NO `default:` and NO `case 0:` -- state 0 and anything above 4 fall through
 * the jump table to the function's implicit end, which is why the ROM's default
 * and case-0 slots are bare pop instructions rather than branches.
 *
 * The release guard tests a 64-bit flag word: the mask 0x40 belongs to the high
 * half, so written as a long long the compiler ands the low word with zero,
 * which is exactly what the ROM does. */
extern void func_ov038_020b3b04(int self, int *p2);
extern void func_ov038_020b41e0(int p2, int a);
extern void func_ov038_020b3cfc(int self, void *block);
extern void func_ov038_020b4234(int self, void *block, int a);
extern unsigned int func_0202a818(void *p, int a);
extern void func_ov022_020a4490(int self, int a, int b);
extern int func_ov022_02095554(void *p);

extern int data_ov038_020b4ca0;

struct Ov038Self {
    char pad000[0x464];
    long long flags464;
    char pad46c[0x250];
    int nStage6bc;
};

void func_ov038_020b3b40(int self, int *p2, int p3) {
    char *blk = (char *)(*(int *)&data_ov038_020b4ca0 + 0x2c + 0x2c00);

    if (*p2 != 0 && (((struct Ov038Self *)self)->nStage6bc != 0x31 ||
                     (((struct Ov038Self *)self)->flags464 & 0x4000000000LL) != 0)) {
        func_ov038_020b3b04(self, p2);
    }
    if (*p2 == 0) {
        return;
    }
    if (*p2 != 4) {
        *(int *)((char *)p2 + 0x10c) += p3;
    }
    switch (*p2) {
    case 1:
        if (*(int *)((char *)p2 + 0x10c) < 0) {
            return;
        }
        func_ov038_020b41e0((int)p2, 0);
        *p2 = 2;
        *(int *)((char *)p2 + 0x10c) = 0;
        return;
    case 2:
        func_0202a818((void *)((char *)p2 + 4), p3);
        if (*(int *)((char *)p2 + 0x10c) < 0xf000) {
            return;
        }
        func_ov022_020a4490(self, 0xc8, 2);
        func_ov038_020b41e0((int)p2, 1);
        func_ov038_020b3cfc(self, blk);
        func_ov038_020b4234(self, blk + 0x118, 0);
        *p2 = 3;
        *(int *)((char *)p2 + 0x10c) = 0;
        return;
    case 3:
        func_0202a818((void *)((char *)p2 + 4), p3);
        if (*(int *)((char *)p2 + 0x10c) < 0xf000) {
            return;
        }
        if (func_ov022_02095554((void *)(self + 0x22f8)) == 0) {
            return;
        }
        func_ov022_020a4490(self, 0xc8, 3);
        func_ov038_020b41e0((int)p2, 2);
        func_ov038_020b3cfc(self, blk);
        func_ov038_020b4234(self, blk + 0x118, 2);
        *p2 = 4;
        *(int *)((char *)p2 + 0x10c) = 0;
        return;
    case 4:
        func_0202a818((void *)((char *)p2 + 4), p3);
        return;
    }
}
