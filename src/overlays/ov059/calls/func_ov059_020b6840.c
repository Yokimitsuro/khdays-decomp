/*
 * Attack burst of the ov040 enemy: on every 0x9000 tick of the +0x7b0 timer (from the first
 * one on) the anchor is sampled and the emitter pointed backwards along the heading (kind
 * 0x4800, range 0x1000, no anchor); the burst parameters take the +0x1000/1 owner slot, flags
 * 0x205 (plus 0x420 in the rig's alternate mode, plus 0x1000 in pattern 2) and the spin by mode
 * and pattern (0x1a00, or 0x1d00 / 0x1e40 for pattern 2 with / without the alternate mode), the
 * fixed 0xa00/0x66/0xa00 extent and no second block; a successful submit that is not busy
 * spawns effect 0x96 at +0x26c8 and, on the real actor, queues action 3 with the alternate
 * mode as its argument. Codegen: the emit kind is assigned after the direction (its constant
 * is then created after the sine-table pointer, which keeps the table in r6) and the owner flag test
 * is the 64-bit AND truncated to int (low word in r1). */
typedef unsigned short u16;
typedef unsigned char u8;

struct Vec3 { int x, y, z; };

struct Emit {
    char pad00[0xc];
    int nKind;
    int nOwner;
    int nDirX;
    int nDirY;
    int nDirZ;
    int nRange;
    void *pAnchor;
    int nFlags28;
};

struct Params {
    void *pA;
    void *pB;
    unsigned int uFlags;
    int w0c;
    u8 b10;
    u8 pad11[3];
    struct Vec3 vExtent;
    int w20;
    u8 pad24;
    u8 b25;
    u8 pad26[2];
};

extern void func_ov022_020ad44c(struct Emit *emit, char *self);
extern void *func_ov022_020a1f84(char *self, int a, int b, int c);
extern void func_ov022_020a23a4(char *self, int spin, void *a, void *b);
extern int func_ov022_020a0fb8(char *self, struct Emit *emit, void *params);
extern void func_ov022_020ad28c(char *self, char *at, int effect, int arg);
extern short data_0203d210[];
extern char *data_ov059_020b7320;

void func_ov059_020b6840(char *self)
{
    struct Emit emit;
    struct Params prm;
    int angle;
    int idx;
    int spin;
    int timer = *(int *)(self + 0x7b0);
    char *rig = data_ov059_020b7320 + 0xc50 + 0x2000;

    if (timer % 0x9000 != 0) {
        return;
    }
    if (timer < 0x9000) {
        return;
    }
    func_ov022_020ad44c(&emit, self);
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.nDirX = -data_0203d210[idx * 2];
    emit.nDirZ = -data_0203d210[idx * 2 + 1];
    emit.nDirY = 0;
    emit.nKind = 0x4800;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = 0;
    emit.nFlags28 = 0;
    prm.pA = func_ov022_020a1f84(self, 0x1000, 0, 1);
    prm.uFlags = 0x205;
    if (*(int *)rig != 0) {
        prm.uFlags |= 0x420;
        if (*(int *)(rig + 4) == 2) {
            prm.uFlags |= 0x1000;
            spin = 0x1d00;
        } else {
            spin = 0x1a00;
        }
    } else {
        if (*(int *)(rig + 4) == 2) {
            prm.uFlags |= 0x1000;
            spin = 0x1e40;
        } else {
            spin = 0x1a00;
        }
    }
    func_ov022_020a23a4(self, spin, &prm.pA, &prm.pB);
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    prm.w20 = 0;
    prm.b10 = 0;
    prm.pB = 0;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    if (func_ov022_020a0fb8(self, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x2000 + 0x6bc) & 1) != 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x2000 + 0x6bc) & 0x40) != 0) {
        return;
    }
    func_ov022_020ad28c(self, self + 0x2c8 + 0x2400, 0x96, 0);
    if (!(int)(*(unsigned long long *)self & 0x10000)) {
        *(u8 *)(self + 0x47a) = 3;
        if (*(int *)rig != 0) {
            *(u8 *)(self + 0x47b) = 1;
        } else {
            *(u8 *)(self + 0x47b) = 0;
        }
    }
}
