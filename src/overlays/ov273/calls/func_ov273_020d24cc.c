/* Lock-on entry of the ov213 enemy: the +0x24 target is picked (020cab14); without one the next
 * move is 2. The +0x38 heading turns to face the target (look-at from the target's +0x74 to the
 * actor's). Once the +8 flag byte clears the +0x3dc companion takes the +0x3ec joint's pose (+4
 * into +0x398) and runs its +0x1cc hook, the actor plays pose 9, +0x434 bit 0 and the companion's
 * +0x394 bit 0 are set (bits 1-2 cleared), the overlay's 14-byte message with the +4 point goes
 * out through the actor's +0x24 hook, the companion plays pose 1 (looping), the +0x1c timer
 * clears, bit 1 of the +0x60 high byte and bit 0 of +0x1ae are set, the +0x3d4 shape is disarmed
 * and the node moves to 020ceb2c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { int w[4]; } Quat;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Msg14 { u16 h[7]; };
struct b1 { unsigned int b0 : 1; };
typedef struct { unsigned f : 8; } B8;
struct At4 { char pad[4]; Quat q; };
struct At398 { char pad[0x398]; Quat q; };

struct Ov213Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov213Actor *self, void *msg, int size);
};

extern int func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_0203cd7c(Mtx33 *out, const void *from, const void *to, const Vec3 *up);
extern void func_0202ea48(void *q, const Mtx33 *m);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern const Vec3 data_02042264;
extern const struct Msg14 data_ov273_020d6b08;
extern void func_ov273_020d276c(void);

#define PACK3(msg, base, v) \
    ((u8 *)(msg))[(base)] = (u8)(((u32)(v) >> 0x10 & 0x7f) | ((u32)(v) >> 0x18 & 0x80)); \
    ((u8 *)(msg))[(base) + 1] = (u8)((u32)(v) >> 8); \
    ((u8 *)(msg))[(base) + 2] = (u8)(v)

void func_ov273_020d24cc(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    struct Msg14 msg;
    FxVec vAt;
    Vec3 *pPos;
    void (*hook)(int, int);

    state[9] = func_ov107_020cab14(*state, 0);
    if (state[9] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_0203cd7c(&mtx, (void *)(state[9] + 0x74), (void *)(*state + 0x74), &data_02042264);
    func_0202ea48(state + 0xe, &mtx);
    if (*(u8 *)state[2] != 0) {
        return;
    }
    ((struct At398 *)*(int *)(*state + 0x3dc))->q = ((struct At4 *)*(int *)(*state + 0x3ec))->q;
    hook = *(void (**)(int, int))(*(int *)(*state + 0x3dc) + 0x1cc);
    if (hook != 0) {
        hook(*(int *)(*state + 0x3dc), 0);
    }
    func_ov107_020c9264(*state, 9, 0);
    ((struct b1 *)(*state + 0x434))->b0 = 1;
    ((struct b1 *)(*(int *)(*state + 0x3dc) + 0x394))->b0 = 1;
    *(int *)(*(int *)(*state + 0x3dc) + 0x394) &= ~2;
    *(int *)(*(int *)(*state + 0x3dc) + 0x394) &= ~4;
    msg = data_ov273_020d6b08;
    pPos = (Vec3 *)state[1];
    vAt.x = *(Fx32 *)&pPos->x;
    PACK3(&msg, 5, vAt.x.value);
    vAt.y = *(Fx32 *)&pPos->y;
    PACK3(&msg, 8, vAt.y.value);
    vAt.z = *(Fx32 *)&pPos->z;
    PACK3(&msg, 11, vAt.z.value);
    ((u8 *)&msg)[4] = 0;
    if (((struct Ov213Actor *)*state)->pfnMessage != 0) {
        ((struct Ov213Actor *)*state)->pfnMessage((struct Ov213Actor *)*state, &msg, 0xe);
    }
    func_ov107_020c9264(*(int *)(*state + 0x3dc), 1, 1);
    state[7] = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    ((B8 *)(*(int *)(*state + 0x3d4) + 8))->f &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov273_020d276c);
}
