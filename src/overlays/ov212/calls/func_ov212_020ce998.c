/* Release the sub-objects and hand off (x3: ov212/266/267). Raise flags 0x86 on the
 * hw60 hi byte, then for each of the 3 tracked sub-objects clear the active bit 0 and
 * raise bit 1, and advance state.
 *
 * The two bit ops on each slot are separate statements that each re-resolve the slot
 * pointer -- the ROM reloads *ctx and re-indexes for both, so caching the slot in a
 * local costs instructions. */
struct b8 { unsigned f : 8; };

extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov212_020cea40(void);

void func_ov212_020ce998(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    int i = 0;
    unsigned short v;

    v = *(unsigned short *)(*ctx + 0x60);
    *(unsigned short *)(*ctx + 0x60) =
        (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    for (; i < 3; i++) {
        ((struct b8 *)(((int *)*ctx)[i + 0x133] + 8))->f &= ~1;
        ((struct b8 *)(((int *)*ctx)[i + 0x133] + 8))->f |= 2;
    }
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov212_020cea40);
}
