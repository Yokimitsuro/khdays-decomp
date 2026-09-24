/* Grab tick: the +0x18 rate is the frame rate x 3 and the +0x1c timer accumulates the frame rate; at
 * 0.53 reaction 0x16c mode 4 fires once at the +4 point (+0x32). Once the timer is at least half of
 * 0.63 (64-bit ratio, capped at 1), a 2.0 sphere at the +0x3ac hand part's +0x14 point grabs, while
 * the +0x3bc slot is empty, the first entity of the scene list that is ready (+0x40 bit 1, +0x60 bit 0,
 * no 0x2000 flag on its +0x18c rider) and within reach, if it accepts a kind 6 hit without push on
 * behalf of the +0x384 rider; a held entity is pulled toward the hand by 2/3 of the ratio. Once the +8
 * idle byte clears: with a catch, message data_ov253_020d497e carries the hand point 1.0 higher to the
 * +0x24 hook, the rider refreshes (020ad8e0), the target is marked held (+0x60 high bit 1), bit 0 of
 * +0x1ae sets, the +0x3b4 part's hit volume turns off, reaction 0x16c mode 5 fires at the hand, the
 * timer clears and the tick hands over to func_ov253_020d01c0; without one, pose 7 plays and the tick
 * hands over to func_ov253_020d0938. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;
struct Bits40 { int bit0 : 1; int bit1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern long long func_01ff8a14(int num, int den);
extern long long func_020201b8(long long a, long long b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, const Vec3 *push, int z);
extern void VEC_Add(const void *a, const Vec3 *b, void *out);
extern void func_ov022_020ad8e0(int a, int b);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov253_020d497e;
extern const Vec3 data_02041dc8;
extern void func_ov253_020d01c0(int *node);
extern void func_ov253_020d0938(void);

void func_ov253_020cfd20(int *node)
{
    int *state = (int *)node[1];
    long long q;
    int scene = *(int *)(*state + 4);
    Sphere sphere;
    Vec3 d;
    Vec3 push;
    Vec3 raw;
    Cmd14 msg;
    FxVec vContact;
    int *entry;
    int other;

    state[6] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[7] += *(int *)(node[0] + 0x2c);
    q = func_01ff8a14(state[7], 0xa22);
    if (q > 0x100000000LL) {
        q = 0x100000000LL;
    }
    if (*((u8 *)state + 0x32) == 0 && state[7] >= 0x888) {
        func_ov107_020c5af8(state[0], 0x16c, 4, (void *)state[1]);
        *((u8 *)state + 0x32) = 1;
    }
    if (q >= 0x80000000LL) {
        sphere.center = *(Vec3 *)(*(int *)(*state + 0x3ac) + 0x14);
        sphere.nRadius = 0x2000;
        if (*(int *)(*state + 0x3bc) == 0) {
            entry = func_01fffd70(scene + 0xa8);
            other = entry == 0 ? 0 : *entry;
            while (other != 0) {
                if (((struct Bits40 *)(other + 0x40))->bit1 && (((struct hw60 *)(other + 0x60))->lo & 1) != 0
                    && (*(u64 **)(other + 0x18c) == 0 || (**(u64 **)(other + 0x18c) & 0x2000) == 0)) {
                    VEC_Subtract((void *)(other + 0x74), &sphere.center, &d);
                    if (func_01ff8d18(&d, &d) <= *(int *)(other + 0x80) + sphere.nRadius
                        && func_ov107_020ca918(other, *state, *(int *)(*state + 0x384), 6, &data_02041dc8, 0) != 0) {
                        *(int *)(*state + 0x3bc) = other;
                        break;
                    }
                }
                entry = func_01fffd8c(scene + 0xa8);
                other = entry == 0 ? 0 : *entry;
            }
        }
        if (*(int *)(*state + 0x3bc) != 0) {
            long long t;

            VEC_Subtract(&sphere.center, (void *)(*(int *)(*state + 0x3bc) + 0x74), &d);
            t = func_020201b8(q * 2, 3);
            push.x = (int)((t * d.x + 0x80000000LL) >> 32);
            push.y = (int)((t * d.y + 0x80000000LL) >> 32);
            push.z = (int)((t * d.z + 0x80000000LL) >> 32);
            VEC_Add((void *)(*(int *)(*state + 0x3bc) + 0xe4), &push, (void *)(*(int *)(*state + 0x3bc) + 0xe4));
        }
    }
    if (*(u8 *)state[2] != 0) {
        return;
    }
    if (*(int *)(*state + 0x3bc) != 0) {
        msg = data_ov253_020d497e;
        raw = *(Vec3 *)(*(int *)(*state + 0x3ac) + 0x14);
        raw.y += 0x1000;
        vContact.x = *(Fx32 *)&raw.x;
        ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 0x10 & 0x7f) | ((u32)vContact.x.value >> 0x18 & 0x80));
        ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
        ((u8 *)&msg)[7] = (u8)vContact.x.value;
        vContact.y = *(Fx32 *)&raw.y;
        ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 0x10 & 0x7f) | ((u32)vContact.y.value >> 0x18 & 0x80));
        ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
        ((u8 *)&msg)[10] = (u8)vContact.y.value;
        vContact.z = *(Fx32 *)&raw.z;
        ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 0x10 & 0x7f) | ((u32)vContact.z.value >> 0x18 & 0x80));
        ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
        ((u8 *)&msg)[13] = (u8)vContact.z.value;
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        func_ov022_020ad8e0(*(int *)(*(int *)(*state + 0x3bc) + 0x18c), 1);
        {
            u16 hw = *(u16 *)(*(int *)(*state + 0x3bc) + 0x60);
            *(u16 *)(*(int *)(*state + 0x3bc) + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
        }
        *(u16 *)(*state + 0x1ae) |= 1;
        ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
        func_ov107_020c5af8(*state, 0x16c, 5, (void *)(*(int *)(*state + 0x3ac) + 0x14));
        state[7] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov253_020d01c0);
        return;
    }
    func_ov107_020c9264(*state, 7, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov253_020d0938);
}
