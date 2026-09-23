/* Rise decision of the ov210 enemy (x3 with ov211/ov282). With any of bits 0-3 of the owner's
 * +0x1c4 set and a target re-acquired into +0x10, the gap to it beyond both radii picks the next
 * sub-state: 0xf within 1.0, 0xa from 8.0, otherwise a d100 roll picks 0xa/0xd/0xc/0xb/9 at
 * 25/50/75/99, and the action ends. Otherwise it performs the rise entry: bits 2, 3 and 6 of the
 * +0x60 high byte and bit 0 of +0x1ae are raised, bit 0 of the +0x3b0 body's +8 low byte clears,
 * animation 6 plays, the +0x2c/+0x30 timers clear, the +4 point is kept at +0x34 and sent packed
 * in the overlay's 14-byte message (data_ov211_020d651c, flag 0) to the owner's +0x24 hook; the
 * +0x60 timer and +0x66 byte clear and the tick hands over to func_ov211_020d327c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 h[7]; } Cmd14;

struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern int func_ov107_020cab14(int owner, int *out);
extern int FX_Sqrt(int v);
extern long long func_02023eb4(int bound);

static inline int RandRange(int lo, int hi) { return (int)func_02023eb4(hi - lo + 1) + lo; }
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov211_020d651c;
extern void func_ov211_020d327c(int *node);

void func_ov211_020d2f6c(int *node)
{
    int *state = (int *)node[1];
    Cmd14 msg;
    int dist;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 *pPos;
    int owner;
    int target;
    int roll;
    u16 v;

    if ((*(u8 *)(*state + 0x1c4) & 0xf) != 0) {
        target = state[4] = func_ov107_020cab14(*state, &dist);
        if (target != 0) {
            owner = *state;
            dist = FX_Sqrt(dist) - (*(int *)(owner + 0x80) + *(int *)(target + 0x80));
            if (dist <= 0x1000) {
                *(u8 *)(*state + 0x1c7) = 0xf;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (dist >= 0x8000) {
                *(u8 *)(*state + 0x1c7) = 0xa;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            roll = RandRange(0, 100);
            if (roll < 0x19) {
                *(u8 *)(*state + 0x1c7) = 0xa;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (roll < 0x32) {
                *(u8 *)(*state + 0x1c7) = 0xd;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (roll < 0x4b) {
                *(u8 *)(*state + 0x1c7) = 0xc;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (roll < 0x63) {
                *(u8 *)(*state + 0x1c7) = 0xb;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            *(u8 *)(*state + 0x1c7) = 9;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    v = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x4c) << 0x18) >> 0x10));
    *(u16 *)(*state + 0x1ae) |= 1;
    ((struct w8 *)(*(int *)(*state + 0x3b0) + 8))->lo &= ~1;
    func_ov107_020c9264(*state, 6, 0);
    state[0xb] = 0;
    state[0xc] = 0;
    *(Vec3 *)(state + 0xd) = *(Vec3 *)state[1];
    msg = data_ov211_020d651c;
    pPos = (Fx32 *)state[1];
    PACK(msg, scratchX, pPos[0], 5);
    PACK(msg, scratchY, pPos[1], 8);
    PACK(msg, scratchZ, pPos[2], 11);
    ((u8 *)&msg)[4] = 0;
    if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
    state[0x18] = 0;
    *(u8 *)((char *)state + 0x66) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov211_020d327c);
}
