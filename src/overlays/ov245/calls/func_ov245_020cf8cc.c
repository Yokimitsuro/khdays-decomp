/* func_ov245_020cf8cc -- message hook: a kind-0 message carries the actor's +0x3b4 position
 * packed as three 24-bit fixed values at bytes 0x26..0x2e (each copied through a stack Fx32
 * first) and the low halfword of the +0x3c0 word at 0x24, then goes to the base forwarder (020c7a90). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } Fx24;

extern void func_ov107_020c7a90(int self, unsigned char *msg, int arg);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

void func_ov245_020cf8cc(int self, unsigned char *msg, int arg) {
    FxVec v;

    if (msg[2] == 0) {
        v.x = *(Fx32 *)(self + 0x3b4);
        PackFx24((Fx24 *)(msg + 0x26), v.x.value);
        v.y = *(Fx32 *)(self + 0x3b8);
        PackFx24((Fx24 *)(msg + 0x29), v.y.value);
        v.z = *(Fx32 *)(self + 0x3bc);
        PackFx24((Fx24 *)(msg + 0x2c), v.z.value);
        *(unsigned short *)(msg + 0x24) = (unsigned short)*(int *)(self + 0x3c0);
    }
    func_ov107_020c7a90(self, msg, arg);
}
