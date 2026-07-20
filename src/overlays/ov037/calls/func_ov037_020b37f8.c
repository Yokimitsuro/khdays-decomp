/*
 * Message handler: 0x21 resets the counter and reports 0x2f; 0x22 runs the launch -- notify,
 * reset the node, set the speed word at +0x7b0 to 0x27000, raise the 64-bit flag pair at +0,
 * set the turn rate at +0x64, and re-aim at the partner.
 *
 * THE 64-BIT OR.  The ROM's `orr rN, rN, #0` is not a no-op and not a macro artifact: it is
 * the HIGH HALF of a 64-bit OR on a pair of adjacent flag words.  `*(long long *)(p) |= mask`
 * emits exactly two loads, `orr` low with the mask, `orr` high with zero, two stores.
 * Everything else tried on this -- plain `|= 0`, volatile `|= 0`, explicit `*p = *p | 0`,
 * volatile pointer locals -- recovers the load and the store but never the orr, because there
 * is no `| 0` in the source to preserve.  It also explains the second oddity: the two-step
 * base (`add r0, r5, #0x64` then `[r0, #0x404]`) is just how mwcc addresses the high half,
 * not a separate source construct.
 */
typedef struct { int x, y, z; } Vec3;

extern void func_ov022_020a2954(char *self);
extern void func_01fff774(char *p, int i, int v);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern char *data_ov037_020b4e20;
extern void func_ov037_020b3d08(void);
extern void func_ov037_020b4104(void);

void *func_ov037_020b37f8(char *self, int msg) {
    char *blk = data_ov037_020b4e20 + 0x2c + 0x2c00;
    void *next = 0;
    Vec3 d;
    unsigned short a;
    int *node;

    switch (msg) {
    case 0x21:
        *(int *)(blk + 0x110) = 0;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        next = (void *)&func_ov037_020b3d08;
        break;
    case 0x22:
        next = (void *)&func_ov037_020b4104;
        func_ov022_020a2954(self);
        (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x27000);
        *(int *)(self + 0x7b0) = 0x27000;
        *(long long *)self |= 0x20000000;
        *(unsigned short *)(self + 0x64) = 0x1800;
        if (func_ov022_020ad114(self) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(self), (const Vec3 *)(self + 0x48c), &d);
            if (VEC_Mag(&d) != 0) {
                func_01ff8d18(&d, &d);
            }
            a = (unsigned short)FX_Atan2(-d.x, -d.z);
            node = *(int **)(self + 0x20);
            if ((node[0] & 0x20) == 0) {
                *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
                *(unsigned short *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    }
    return next;
}
