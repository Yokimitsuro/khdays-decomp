/* func_ov253_020cfa44 -- roar tick: the +0x18 speed follows twice the frame step (30 / 15);
 * until the +0x30 latch is set the +0x1c timer runs up and past 0.267 the overlay's 14-byte
 * message (data_ov253_020d499a) carrying the +4 position as three 24-bit coordinates goes
 * through the actor's +0x24 hook and the latch is raised. Once the +8 item's animation is free
 * sub-state 2 is requested and the node slot released. Codegen: the position is packed through
 * Fx32 wrapper copies (ov269_3930 idiom) -- the three unread word stores are the ROM's. */
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

extern void func_0203c634(int *node, int slot, void *cb);
extern const PosMsg data_ov253_020d499a;

void func_ov253_020cfa44(int *node) {
    int *state = (int *)node[1];
    PosMsg msg;
    FxVec vContact;
    FxVec *src;

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    if (*((u8 *)state + 0x30) == 0) {
        state[7] += *(int *)(node[0] + 0x2c);
        if (state[7] >= 0x444) {
            msg = data_ov253_020d499a;
            src = (FxVec *)state[1];
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
            *((u8 *)state + 0x30) = 1;
        }
    }
    if (*(u8 *)state[2] != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
