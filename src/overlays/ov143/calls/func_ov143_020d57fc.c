/* One frame of the ground slam (Ghidra: Ov143_StepSlamProbe).
 *
 * Re-aims the sub-object at its stored facing, clears its velocity, turns the
 * appearance flags to the slam pose and re-arms the particle pool entry. It then
 * takes the facing, converts it to a yaw, rotates the fixed 2.0 unit probe by
 * that yaw and sweeps a 0x280 sphere from the owning actor's centre.
 *
 * A miss just hands the task on to the next step. A hit patches the fourteen
 * byte placement command with the anchor position packed as three sign-plus-
 * magnitude 24-bit components, broadcasts it through the object's message hook,
 * clears the sub-state and ends the action. That command is type 5 action 1 --
 * exactly the shape the spawn handlers read back.
 *
 * The anchor position is also written to a twelve-byte stack copy nothing ever
 * reads, one word at a time through a one-word struct: that is what keeps the
 * store alive through dead-store elimination so it fuses with the packing.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Word { int w; };
struct Ov143Cmd { u16 h[7]; };
struct Ov143Mtx33 { int m[9]; };
struct Ov143Quat { int q[4]; };
struct Ov143Hw60 { u16 lo : 8, hi : 8; };
struct Ov143PoolEntry { int value; int pad04; unsigned int flags : 8; };

struct Ov143SubObj {
    char pad000[4];
    void *pScene;                                                  /* 0x004 */
    char pad008[0x1c];
    void (*pMsgHook24)(struct Ov143SubObj *self, void *msg, int len); /* 0x024 */
    char pad028[0x38];
    u16 hwFlags60;                                                 /* 0x060 */
    char pad062[0x3e];
    char aSrtA0[0x2c];                                             /* 0x0a0 */
    char pad0cc[0xfb];
    u8 bSubState1c7;                                               /* 0x1c7 */
    char pad1c8[0x1c0];
    struct Ov143PoolEntry *pPoolEntry388;                          /* 0x388 */
    struct Vec3 vFacing38c;                                        /* 0x38c */
    char *pOwner398;                                               /* 0x398 */
};

struct Ov143StepState {
    struct Ov143SubObj *pSelf;   /* 0x00 */
    struct Vec3 *pAnchor;        /* 0x04 */
    struct Vec3 vVelocity08;     /* 0x08 */
    struct Vec3 vFacing14;       /* 0x14 */
    int nUnused20;               /* 0x20 */
    int nUnused24;               /* 0x24 */
    int nSpeed28;                /* 0x28 */
};

struct Ov143StepNode {
    void *pClock;                /* 0x00 */
    struct Ov143StepState *pState; /* 0x04 */
    char pad08[0x18];
    signed char bSlot;           /* 0x20 */
};

extern struct Vec3 data_02042258;
extern struct Vec3 data_ov143_020d6264;
extern struct Ov143Cmd data_ov143_020d627e;
extern const short data_0203d210[];
extern void func_ov143_020d5ab0(void);

extern void func_0202ed60(struct Ov143Quat *out, const struct Vec3 *from,
                          const struct Vec3 *to);
extern void func_0203c9d0(void *srt, const struct Ov143Quat *rot);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const struct Vec3 *src, struct Vec3 *dst);
extern void MTX_RotY33_(struct Ov143Mtx33 *m, int sine, int cosine);
extern void MTX_MultVec33(const struct Vec3 *v, const struct Ov143Mtx33 *m,
                          struct Vec3 *out);
extern void *func_01fff948(void *collision, const struct Vec3 *origin,
                           const struct Vec3 *dir, int radius);
extern void func_0203c634(struct Ov143StepNode *node, int slot, void *value);

#define ANGLE_TO_INDEX(angle) \
    ((u16)((int)(((long long)(angle) * 0x28be60db9391LL + 0x80000000000LL) >> 44)) >> 4)

void func_ov143_020d57fc(struct Ov143StepNode *node)
{
    struct Ov143StepState *state = node->pState;
    struct Ov143Quat rot;
    struct Ov143Mtx33 mtx;
    struct Vec3 probe;
    struct Ov143Cmd cmd;
    struct Vec3 vDead;
    void *scene;
    int angle;
    int index;
    void *hit;
    struct Word *s;
    unsigned int flags;

    func_0202ed60(&rot, &data_02042258, &state->vFacing14);
    func_0203c9d0(state->pSelf->aSrtA0, &rot);
    state->nUnused20 = 0;
    state->nUnused24 = 0;

    /* The set is written out longhand and the clear through the bit-field: the
       clear is the one that needs the container truncated back to sixteen bits,
       and spelling both as bit-fields puts that truncation on the set too. */
    flags = state->pSelf->hwFlags60;
    state->pSelf->hwFlags60 = flags & ~0xff00
        | (((((flags << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    ((struct Ov143Hw60 *)&state->pSelf->hwFlags60)->hi &= ~0x8c;
    state->pSelf->pPoolEntry388->flags |= 1;

    state->vFacing14 = state->pSelf->vFacing38c;
    angle = func_020050b4(state->vFacing14.x, state->vFacing14.z);
    state->nSpeed28 = 0x800;
    func_01ffa724(0x800, &state->vFacing14, &state->vVelocity08);

    scene = state->pSelf->pScene;
    probe = data_ov143_020d6264;
    index = ANGLE_TO_INDEX(angle);
    MTX_RotY33_(&mtx, data_0203d210[index * 2], data_0203d210[index * 2 + 1]);
    MTX_MultVec33(&probe, &mtx, &probe);
    hit = func_01fff948(*(void **)((char *)scene + 0x7c),
                        (struct Vec3 *)(state->pSelf->pOwner398 + 0xb0),
                        &probe, 0x280);
    if (hit != 0) {
        cmd = data_ov143_020d627e;
        s = (struct Word *)state->pAnchor;

        *(struct Word *)&vDead.x = s[0];
        ((u8 *)&cmd)[5] = (u8)(((unsigned int)vDead.x >> 0x10 & 0x7f)
                           | ((unsigned int)vDead.x >> 0x18 & 0x80));
        ((u8 *)&cmd)[6] = (u8)((unsigned int)vDead.x >> 8);
        ((u8 *)&cmd)[7] = (u8)vDead.x;

        *(struct Word *)&vDead.y = s[1];
        ((u8 *)&cmd)[8] = (u8)(((unsigned int)vDead.y >> 0x10 & 0x7f)
                           | ((unsigned int)vDead.y >> 0x18 & 0x80));
        ((u8 *)&cmd)[9] = (u8)((unsigned int)vDead.y >> 8);
        ((u8 *)&cmd)[10] = (u8)vDead.y;

        *(struct Word *)&vDead.z = s[2];
        ((u8 *)&cmd)[11] = (u8)(((unsigned int)vDead.z >> 0x10 & 0x7f)
                            | ((unsigned int)vDead.z >> 0x18 & 0x80));
        ((u8 *)&cmd)[12] = (u8)((unsigned int)vDead.z >> 8);
        ((u8 *)&cmd)[13] = (u8)vDead.z;

        if (state->pSelf->pMsgHook24 != 0) {
            state->pSelf->pMsgHook24(state->pSelf, &cmd, 0xe);
        }
        state->pSelf->bSubState1c7 = 0;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    func_0203c634(node, node->bSlot, func_ov143_020d5ab0);
}
