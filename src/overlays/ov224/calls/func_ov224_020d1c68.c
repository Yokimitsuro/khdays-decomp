/* Resets the ov224 sub-object: clears +0x78, patches the two flag bytes packed into the
 * halfword at +0x60 of the owner (|0xc0 then |0xe), raises bit 0 of the halfword at +0x1ae,
 * clears bit 0 of the low byte of +8 on all five entries of the list at +0x3ac, wipes the
 * 0x48-byte block through func_ov107_020c5af8, clears +0x5c and re-arms func_0203c634.
 *
 * The previous file here described a completely different function (a func_0203c5c0 spawn)
 * and never matched.  Two levers were needed:
 *  - the high byte of +0x60 is a BITFIELD read (`lsl #16 / lsr #24`) but the insert has to be
 *    written by hand: as a pure bitfield assignment mwcc adds a second `lsl #16 / lsr #16`
 *    truncation back to the container before merging.
 *  - the entry list is an ARRAY INDEX with 0x3ac folded in (0x3ac/4 = 0xeb); spelled
 *    `base + i * 4 + 0x3ac` mwcc builds a second byte-offset induction variable. */
struct Bits60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

struct Bits08 {
    unsigned int f : 8;
};

extern void func_ov107_020c5af8(char *o, int a, int b, void *p);
extern void func_0203c634(char *self, int a, void *cb);
extern void func_ov224_020d1d44(int);

void func_ov224_020d1c68(char *self) {
    char *ctx = *(char **)(self + 4);
    int i = 0;
    char *o;
    struct Bits60 *b;
    *(int *)(ctx + 0x78) = i;
    b = (struct Bits60 *)(*(char **)ctx + 0x60);
    *(unsigned short *)b = (unsigned short)((*(unsigned short *)b & ~0xff00u) | (((b->hi | 0xc0u) << 24) >> 16));
    b = (struct Bits60 *)(*(char **)ctx + 0x60);
    *(unsigned short *)b = (unsigned short)((*(unsigned short *)b & ~0xff00u) | (((b->hi | 0xeu) << 24) >> 16));
    *(unsigned short *)(*(char **)ctx + 0x1ae) |= 1;
    do {
        o = ((char **)*(char **)ctx)[i + 0xeb];
        i = i + 1;
        ((struct Bits08 *)(o + 8))->f &= ~1;
    } while (i < 5);
    func_ov107_020c5af8(*(char **)ctx, 0, 0x48, *(void **)(ctx + 8));
    *(int *)(ctx + 0x5c) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), (void *)func_ov224_020d1d44);
}
