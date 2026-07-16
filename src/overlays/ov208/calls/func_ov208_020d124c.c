/* func_ov208_020d124c -- ov208's move dispatcher, with an orientation update in front.
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
extern void func_ov208_020d15b0(void);
extern void func_ov208_020d167c(void);
extern void func_ov208_020d1840(void);
extern void func_ov208_020d18d4(void);
extern void func_ov208_020d1e84(void);
extern void func_ov208_020d227c(void);
extern void func_ov208_020d24d4(void);
extern void func_ov208_020d26ac(void);
extern void func_ov208_020d289c(void);
extern void func_ov208_020d2914(void);
extern void func_ov208_020d2bec(void);
extern void func_ov208_020d3420(void);
extern void func_ov208_020d3510(void);

void func_ov208_020d124c(int self) {
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
        func_0203c634(self, 1, func_ov208_020d15b0);
        break;
    case 1:
        func_0203c634(self, 1, func_ov208_020d167c);
        break;
    case 2:
        func_0203c634(self, 1, func_ov208_020d1840);
        break;
    case 4:
        func_0203c634(self, 1, func_ov208_020d18d4);
        break;
    case 5:
        func_0203c634(self, 1, func_ov208_020d1e84);
        break;
    case 6:
        func_0203c634(self, 1, func_ov208_020d227c);
        break;
    case 7:
        func_0203c634(self, 1, func_ov208_020d24d4);
        break;
    case 3:
        func_0203c634(self, 1, func_ov208_020d3420);
        break;
    case 8:
        func_0203c634(self, 1, func_ov208_020d26ac);
        break;
    case 9:
        func_0203c634(self, 1, func_ov208_020d289c);
        break;
    case 10:
        func_0203c634(self, 1, func_ov208_020d2914);
        break;
    case 11:
        func_0203c634(self, 1, func_ov208_020d2bec);
        break;
    case 12:
        func_0203c634(self, 1, func_ov208_020d3510);
        break;
    }

    *(signed char *)(ctx[0] + 0x1c7) = -1;
}
