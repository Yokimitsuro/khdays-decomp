/* Message hook of the ov223 enemy: a kind-0 message carries the actor's +0xbc position packed
 * as three 24-bit values at 0x24 (x first), then goes to the base forwarder (020c7a90). */
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

void func_ov223_020d42e0(int self, unsigned char *msg, int arg) {
    FxVec v;

    if (msg[2] == 0) {
        v.x = *(Fx32 *)(self + 0xbc);
        PackFx24((Fx24 *)(msg + 0x24), v.x.value);
        v.y = *(Fx32 *)(self + 0xc0);
        PackFx24((Fx24 *)(msg + 0x27), v.y.value);
        v.z = *(Fx32 *)(self + 0xc4);
        PackFx24((Fx24 *)(msg + 0x2a), v.z.value);
    }
    func_ov107_020c7a90(self, msg, arg);
}
