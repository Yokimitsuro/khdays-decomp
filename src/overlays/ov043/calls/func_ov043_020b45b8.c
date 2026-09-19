/* Attack burst of the mission enemy: the owner block's +0x124 timer accumulates the actor's
 * +0x2aba rate and fires every 0x15000. The anchor is sampled, raised 0x800 and the emitter
 * pointed backwards along the heading (kind 0x2333, range 0x1000, no anchor); the burst takes
 * spin 0x1900, flags 0x205, the fixed 0xa00/0x66/0xa00 extent and no second block. A successful
 * submit that is not busy spawns effect 0xc4 (arg 2) at +0x26c8. */
typedef unsigned short u16;
typedef unsigned char u8;

struct Vec3 { int x, y, z; };

struct Emit {
    int w00;
    int nY;
    int w08;
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
extern void func_ov022_020a23a4(char *self, int spin, void *a, void *b);
extern int func_ov022_020a0fb8(char *self, struct Emit *emit, void *params);
extern void func_ov022_020ad28c(char *self, char *at, int effect, int arg);
extern short data_0203d210[];
extern char *data_ov043_020b58e0;

void func_ov043_020b45b8(char *self)
{
    struct Emit emit;
    struct Params prm;
    int angle;
    int idx;
    char *pBlock = data_ov043_020b58e0 + 0x138 + 0x2c00;

    *(int *)(pBlock + 0x124) += *(short *)(self + 0x2a00 + 0xba);
    if (*(int *)(pBlock + 0x124) < 0x15000) {
        return;
    }
    *(int *)(pBlock + 0x124) = 0;
    func_ov022_020ad44c(&emit, self);
    emit.nY += 0x800;
    angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    emit.nDirX = -data_0203d210[idx * 2];
    emit.nDirZ = -data_0203d210[idx * 2 + 1];
    emit.nDirY = 0;
    emit.nKind = 0x2333;
    emit.nOwner = *(short *)(self + 0x66);
    emit.nRange = 0x1000;
    emit.pAnchor = 0;
    emit.nFlags28 = 0;
    func_ov022_020a23a4(self, 0x1900, &prm.pA, &prm.pB);
    prm.uFlags = 0x205;
    prm.w0c = 0;
    prm.vExtent.x = 0xa00;
    prm.vExtent.y = 0x66;
    prm.vExtent.z = 0xa00;
    prm.w20 = 0;
    prm.b10 = 0;
    prm.b25 &= ~1;
    prm.b25 &= ~2;
    if (func_ov022_020a0fb8(self, &emit, &prm) == 0) {
        return;
    }
    if ((*(unsigned int *)(self + 0x2000 + 0x6bc) & 0x40) != 0) {
        return;
    }
    func_ov022_020ad28c(self, self + 0x2c8 + 0x2400, 0xc4, 2);
}
