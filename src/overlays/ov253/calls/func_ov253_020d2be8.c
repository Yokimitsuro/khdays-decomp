/* func_ov253_020d2be8 -- grow tick: the +0x1c timer runs up and its 32.32 ratio over 0.5
 * (clamped to 1.0) drives the actor's +0x38c / +0x394 scale from 1.0 up to 3.0 and the +0x390
 * scale from 1.0 down to 0.5; once the ratio reaches 1.0 the overlay's 14-byte message
 * (data_ov253_020d49f0) carrying the +0x388 item's +0x394 joint anchor as three 24-bit
 * coordinates goes through the actor's +0x24 hook, the timer restarts, reaction 0x16b/8 fires
 * on the item at that anchor and the node moves to 020d2db0. Codegen: the anchor is packed
 * through Fx32 wrapper copies (ov269_3930 idiom). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

extern long long func_01ff8a14(int num, int den);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern const PosMsg data_ov253_020d49f0;
extern void func_ov253_020d2db0(void);

void func_ov253_020d2be8(int *node) {
    int *state = (int *)node[1];
    long long q;
    PosMsg msg;
    FxVec vContact;
    FxVec *src;

    state[7] += *(int *)(node[0] + 0x2c);
    q = func_01ff8a14(state[7], 0x800);
    if (q > 0x100000000LL) {
        q = 0x100000000LL;
    }
    *(int *)(*state + 0x38c) = (int)((q * 0x2000LL + 0x80000000LL) >> 32) + 0x1000;
    *(int *)(*state + 0x390) = (int)((q * -0x800LL + 0x80000000LL) >> 32) + 0x1000;
    *(int *)(*state + 0x394) = (int)((q * 0x2000LL + 0x80000000LL) >> 32) + 0x1000;
    if (q < 0x100000000LL) {
        return;
    }
    msg = data_ov253_020d49f0;
    src = (FxVec *)(*(int *)(*(int *)(*state + 0x388) + 0x394) + 0x14);
    vContact.x = src->x;
    ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 0x10 & 0x7f) | ((u32)vContact.x.value >> 0x18 & 0x80));
    ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
    ((u8 *)&msg)[7] = (u8)vContact.x.value;
    vContact.y = src->y;
    ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 0x10 & 0x7f) | ((u32)vContact.y.value >> 0x18 & 0x80));
    ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
    ((u8 *)&msg)[10] = (u8)vContact.y.value;
    vContact.z = src->z;
    ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 0x10 & 0x7f) | ((u32)vContact.z.value >> 0x18 & 0x80));
    ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
    ((u8 *)&msg)[13] = (u8)vContact.z.value;
    if (*(void **)(*state + 0x24) != 0) {
        (*(void (**)(int, PosMsg *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
    state[7] = 0;
    func_ov107_020c5af8(*(int *)(*state + 0x388), 0x16b, 8, (void *)(*(int *)(*(int *)(*state + 0x388) + 0x394) + 0x14));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d2db0);
}
