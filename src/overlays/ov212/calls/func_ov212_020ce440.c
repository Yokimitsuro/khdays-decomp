extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov212_020ce998(void);
extern void func_ov212_020ce50c(void);
extern void func_ov212_020ce800(void);

struct b8 { unsigned f : 8; };

/* Enter/reset this actor's state (x3: ov212/266/267). Clear the give-up byte
 * (+0x1c6) and arm the target slot (+0x1c7 = -1 = none), then drop the "active"
 * bit 0 on each of the 3 tracked sub-objects (owner[0x4cc..0x4d4]), point the
 * work pointer at owner+0xb0, raise flags 6 in the hi byte of the hw60 word, and
 * register the three phase callbacks. */
void func_ov212_020ce440(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int i;
    unsigned short v;

    *(char *)(*ctx + 0x1c6) = 0;
    *(signed char *)(*ctx + 0x1c7) = -1;
    for (i = 0; i < 3; i++) {
        /* 0x133 * 4 == 0x4cc: indexed off the owner base, which is what keeps the
         * scale in the load (`add r2,r2,r1,lsl #2`) instead of strength-reducing
         * it into a second byte-offset induction variable. */
        ((struct b8 *)(((int *)*ctx)[i + 0x133] + 8))->f &= ~1;
    }
    ctx[2] = *ctx + 0xb0;
    v = *(unsigned short *)(*ctx + 0x60);
    *(unsigned short *)(*ctx + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    func_0203c634(self, 1, func_ov212_020ce998);
    func_0203c634(self, 0, func_ov212_020ce50c);
    func_0203c634(self, 2, func_ov212_020ce800);
}
