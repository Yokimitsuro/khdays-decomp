/* Message handler: arm the follow-up state for 0x21 and 0x22, and on 0x22 also re-aim at
 * the partner.
 *
 * Sibling of Ov*_HandleMsgAndFacePartner (328 B, ov046 and company) with one extra step:
 * here the mode at +0x228 selects BOTH the value written to +4 (0, 1, 2) and the code sent
 * to the owner (0x2f, 0x32, 0x30), and there is an additional notify before the aim.
 *
 * Same three levers as that sibling, applied straight from the catalogue and matched on the
 * first compile: both dispatches are SWITCH statements (the ROM jumps to each case, an
 * if-chain falls into the next test and gets predicated), func_ov022_020ad0c0's RETURN
 * VALUE is VEC_Subtract's first argument, and the anchor is self+0x48c reached as one
 * offset even though the ROM splits it into +0x8c and +0x400.
 */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *dst);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern void func_ov022_020a2954(char *self);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern char *data_ov038_020b4ca0;
extern void func_ov038_020b4794(void);
extern void func_ov038_020b4940(void);

void *func_ov038_020b3618(char *self, int msg) {
    char *blk = data_ov038_020b4ca0 + 0x2c + 0x2c00;
    void *next = 0;
    Vec3 d;
    unsigned short a;
    int *node;
    int code;

    switch (msg) {
    case 0x21:
        next = (void *)&func_ov038_020b4794;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        break;
    case 0x22:
        next = (void *)&func_ov038_020b4940;
        switch (*(int *)(blk + 0x228)) {
        case 2:  *(int *)(blk + 4) = 0; code = 0x2f; break;
        case 3:  *(int *)(blk + 4) = 1; code = 0x32; break;
        case 4:  *(int *)(blk + 4) = 2; code = 0x30; break;
        }
        (*(void (**)(char *, int))(self + 0x664))(self, code);
        func_ov022_020a2954(self);
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
