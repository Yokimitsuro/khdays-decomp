typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

typedef struct {
    unsigned bit0 : 1;
    unsigned bit1 : 1;
} Bits2;

typedef struct {
    signed trackHits : 1;
    signed trackPos : 1;
} HitFlags;

extern void func_0203ca30(void *dst, const void *src);
extern void func_0202f188(int *quat, int *axis, int angle);
extern int func_0203c9d0(void *dst, void *src);
extern void func_ov107_020c4ecc(int node);
extern unsigned int func_02033d0c(unsigned int id, unsigned int kind, unsigned int *vec, unsigned int extra);

void func_ov107_020c49b8(int self, u8 *msg) {
    int axis[3];
    int quat[4];
    int pos[3];
    int hitPos[3];
    int posRaw[3];
    int hitRaw[3];
    u16 flags;
    int owner;
    int hitTarget;

    if (msg[2] == 0) {
        flags = *(u16 *)(self + 0x60);
        flags = (u16)((flags & ~0xff) | msg[4]);
        *(u16 *)(self + 0x60) = flags;

        owner = *(int *)(self + 0x9c);
        if (owner != 0) {
            unsigned int b = (unsigned int)(*(u16 *)(self + 0x60) << 24) >> 24;
            ((Bits2 *)(owner + 0x5c))->bit1 = (b & 0x80) ? 1 : 0;
        }

        if (!((unsigned int)(*(u16 *)(self + 0x60) << 24) >> 24 & 1)) {
            return;
        }

        ((char *)posRaw)[3] = msg[0x14];
        ((char *)posRaw)[2] = msg[0x15];
        ((char *)posRaw)[1] = msg[0x16];
        pos[0] = posRaw[0] >> 8;

        ((char *)(posRaw + 1))[3] = msg[0x17];
        ((char *)(posRaw + 1))[2] = msg[0x18];
        ((char *)(posRaw + 1))[1] = msg[0x19];
        pos[1] = posRaw[1] >> 8;

        ((char *)(posRaw + 2))[3] = msg[0x1a];
        ((char *)(posRaw + 2))[2] = msg[0x1b];
        ((char *)(posRaw + 2))[1] = msg[0x1c];
        pos[2] = posRaw[2] >> 8;

        func_0203ca30((void *)(self + 0xa0), pos);

        axis[0] = *(s16 *)(msg + 6);
        axis[1] = *(s16 *)(msg + 8);
        axis[2] = *(s16 *)(msg + 0xa);
        func_0202f188(quat, axis, *(s16 *)(msg + 0xc));
        func_0203c9d0((void *)(self + 0xa0), quat);

        *(int *)(self + 0xcc) = *(s16 *)(msg + 0xe);
        *(int *)(self + 0xd0) = *(s16 *)(msg + 0x10);
        *(int *)(self + 0xd4) = *(s16 *)(msg + 0x12);
        func_ov107_020c4ecc(self);
        return;
    }

    if (msg[2] == 7) {
        hitTarget = *(int *)(self + 4);
        if (hitTarget == 0) {
            return;
        }
        if (!((HitFlags *)(hitTarget + 0x40))->trackHits) {
            return;
        }
        if (!(((HitFlags *)(hitTarget + 0x40))->trackPos && *(s16 *)(msg + 4) != -1)) {
            return;
        }

        ((char *)hitRaw)[3] = msg[8];
        ((char *)hitRaw)[2] = msg[9];
        ((char *)hitRaw)[1] = msg[0xa];
        hitPos[0] = hitRaw[0] >> 8;

        ((char *)(hitRaw + 1))[3] = msg[0xb];
        ((char *)(hitRaw + 1))[2] = msg[0xc];
        ((char *)(hitRaw + 1))[1] = msg[0xd];
        hitPos[1] = hitRaw[1] >> 8;

        ((char *)(hitRaw + 2))[3] = msg[0xe];
        ((char *)(hitRaw + 2))[2] = msg[0xf];
        ((char *)(hitRaw + 2))[1] = msg[0x10];
        hitPos[2] = hitRaw[2] >> 8;

        func_02033d0c(*(s16 *)(msg + 4), *(u16 *)(msg + 6), (unsigned int *)hitPos, 0);
        return;
    }

    if (msg[2] == 0xa) {
        *(u8 *)(self + 0x179) = msg[3];
    }
}
