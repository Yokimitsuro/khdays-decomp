/* func_ov268_020d1254 -- ov208's move dispatcher, with an orientation update in front.
 *
 * ★ That update runs BEFORE the "nothing queued" check, so it happens on every tick whether or not
 * a move is pending: the angle at ctx+0x30 is turned into a quaternion about the constant axis
 * data_02042264 and pushed into the sub-object at ctx[0]+0xa0. The other dispatchers do their work
 * only when a move is queued.
 *
 * The "nothing queued" case then RETURNS outright (a predicated `popeq`) rather than falling into
 * the shared -1 store, as in ov213.
 *
 * The reset drops 0xce from the hw60 hi-byte and bit 0 of the halfword at +0x1ae, then sets bit 0
 * on ctx[0]+0x3b8 and bits 0-1 on ctx[0]+0x3b4.
 *
 * The hw60 write HAS the lsl#0x10/lsr#0x10 trunc pair -> bitfield form; the +8 fields are
 * byte-in-word. See codegen-cracks.md. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quaternion;

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

extern void func_0202f188(Quaternion *out, const VecFx32 *axis, int angle);
extern void func_0203c9d0(int obj, const Quaternion *q);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern VecFx32 data_02042264;
extern void func_ov268_020d15b8(void);
extern void func_ov268_020d1684(void);
extern void func_ov268_020d1848(void);
extern void func_ov268_020d18dc(void);
extern void func_ov268_020d1e8c(void);
extern void func_ov268_020d2284(void);
extern void func_ov268_020d24e0(void);
extern void func_ov268_020d26bc(void);
extern void func_ov268_020d28b0(void);
extern void func_ov268_020d2928(void);
extern void func_ov268_020d2c04(void);
extern void func_ov268_020d3444(void);
extern void func_ov268_020d3534(void);

void func_ov268_020d1254(int self) {
    int *ctx;
    Quaternion q;

    ctx = *(int **)(self + 4);
    func_0202f188(&q, &data_02042264, ctx[0xc]);
    func_0203c9d0(ctx[0] + 0xa0, &q);

    if (*(signed char *)(ctx[0] + 0x1c7) == -1) {
        return;
    }

    *(signed char *)(ctx[0] + 0x1c6) = *(signed char *)(ctx[0] + 0x1c7);
    ((Hw60 *)(ctx[0] + 0x60))->hi &= ~0xce;
    *(unsigned short *)(ctx[0] + 0x1ae) &= ~1;
    ((B8 *)(*(int *)(ctx[0] + 0x3b8) + 8))->f |= 1;
    ((B8 *)(*(int *)(ctx[0] + 0x3b4) + 8))->f |= 3;

    switch (*(signed char *)(ctx[0] + 0x1c6)) {
    case 0:
        func_0203c634(self, 1, func_ov268_020d15b8);
        break;
    case 1:
        func_0203c634(self, 1, func_ov268_020d1684);
        break;
    case 2:
        func_0203c634(self, 1, func_ov268_020d1848);
        break;
    case 4:
        func_0203c634(self, 1, func_ov268_020d18dc);
        break;
    case 5:
        func_0203c634(self, 1, func_ov268_020d1e8c);
        break;
    case 6:
        func_0203c634(self, 1, func_ov268_020d2284);
        break;
    case 7:
        func_0203c634(self, 1, func_ov268_020d24e0);
        break;
    case 3:
        func_0203c634(self, 1, func_ov268_020d3444);
        break;
    case 8:
        func_0203c634(self, 1, func_ov268_020d26bc);
        break;
    case 9:
        func_0203c634(self, 1, func_ov268_020d28b0);
        break;
    case 10:
        func_0203c634(self, 1, func_ov268_020d2928);
        break;
    case 11:
        func_0203c634(self, 1, func_ov268_020d2c04);
        break;
    case 12:
        func_0203c634(self, 1, func_ov268_020d3534);
        break;
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
