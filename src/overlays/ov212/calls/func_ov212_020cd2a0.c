/* func_ov212_020cd2a0 -- message hook: a kind-0 message carries the +0x38c item's grab flag
 * (bit 1 of its +0x5c, as a signed byte) at 0x24 and, unless set, the sixteen +0x38c items'
 * +0x40 positions packed as three 24-bit fixed values per 9-byte slot from 0x28 (each copied
 * through a stack Fx32 first), the current item's +0x54 low halfword at 0x26, and for the last
 * item its +0x54 height (x0.85) turned by its +0x30 pose and added to its position, packed at
 * 0x31. Then the base forwarder (020c7a90) runs. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } Fx24;
typedef struct { int x, y, z; } Vec3;
struct b2 { int b0 : 1, b1 : 1; };
struct Items { char pad[0x38c]; char *items[16]; };

extern void func_0202f384(Vec3 *out, void *pose, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c7a90(int self, unsigned char *msg, int arg);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void VEC_Set(Vec3 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov212_020cd2a0(int self, unsigned char *msg, int arg) {
    Vec3 w;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 tipZ;
    Fx32 tipY;
    Fx32 tipX;
    int i;
    char *item;
    unsigned char *slot;

    if (msg[2] == 0) {
        msg[0x24] = ((struct b2 *)(*(int *)(self + 0x38c) + 0x5c))->b1;
        if (msg[0x24] == 0) {
            slot = msg;
            for (i = 0; i < 16; i++) {
                item = ((struct Items *)self)->items[i];
                *(unsigned short *)(msg + 0x26) = (unsigned short)*(int *)(item + 0x54);
                scratchX = *(Fx32 *)(item + 0x40);
                PackFx24((Fx24 *)(slot + 0x28), scratchX.value);
                scratchY = *(Fx32 *)(item + 0x44);
                PackFx24((Fx24 *)(slot + 0x2b), scratchY.value);
                scratchZ = *(Fx32 *)(item + 0x48);
                PackFx24((Fx24 *)(slot + 0x2e), scratchZ.value);
                if (i == 15) {
                    VEC_Set(&w, 0, 0, FX_Mul(*(int *)(item + 0x54), 0xd9a));
                    func_0202f384(&w, item + 0x30, &w);
                    VEC_Add(&w, (Vec3 *)(item + 0x40), &w);
                    tipX = *(Fx32 *)&w.x;
                    PackFx24((Fx24 *)(slot + 0x31), tipX.value);
                    tipY = *(Fx32 *)&w.y;
                    PackFx24((Fx24 *)(slot + 0x34), tipY.value);
                    tipZ = *(Fx32 *)&w.z;
                    PackFx24((Fx24 *)(slot + 0x37), tipZ.value);
                }
                slot += 9;
            }
        }
    }
    func_ov107_020c7a90(self, msg, arg);
}
