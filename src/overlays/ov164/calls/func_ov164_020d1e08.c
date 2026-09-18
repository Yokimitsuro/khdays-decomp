/* func_ov164_020d1e08: ported from a matched sibling family (same shape, constants and offsets adjusted). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/*
 * Coordinates are held in a one-value wrapper type (Fx32), a tentative
 * reconstruction of the original's coordinate type. Copying a wrapped value is
 * a struct copy, which mwcc keeps, and that is the ROM's unread stack copy of
 * the position.
 */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

struct Msg {
    u16 h[7];
};

struct Comp388 {
    char pad00[8];
    u32 bLow : 8;
};

struct State {
    char *pActor;
    char pad04[0x2c];
    int nField30;
    char pad34[0x1c];
    FxVec *pPos40;
    int nParam44;
    char pad48[4];
    int nField4c;
    int nField50;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void func_ov107_020c9264(char *actor, int a, int b);
extern void func_ov107_020c5af8(char *actor, int id, u16 mode, int param);
extern void func_0203c634(struct Node *node, int slot, void *next);
extern const struct Msg data_ov164_020d2cba;
extern void func_ov164_020d1fd4(void);

void func_ov164_020d1e08(struct Node *node)
{
    struct State *st;
    struct Msg msg;
    FxVec raw;
    FxVec *pPos;
    u16 *hw;
    unsigned int h;
    void (*pfnHook)(char *, struct Msg *, int);

    st = node->pState;

    hw = (u16 *)(st->pActor + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((u32)h << 0x10) >> 0x18 | 0x46) << 0x18) >> 0x10);
    *(u16 *)(st->pActor + 0x1ae) |= 1;
    ((struct Comp388 *)*(void **)(st->pActor + 0x388))->bLow &= ~1;
    *(u8 *)(st->pActor + 0x1c5) &= ~0xf;

    msg = data_ov164_020d2cba;

    pPos = st->pPos40;
    raw.x = pPos->x;
    ((u8 *)&msg)[5] = (u8)(((u32)raw.x.value >> 16 & 0x7f) | ((u32)raw.x.value >> 24 & 0x80));
    ((u8 *)&msg)[6] = (u8)((u32)raw.x.value >> 8);
    ((u8 *)&msg)[7] = (u8)raw.x.value;
    raw.y = pPos->y;
    ((u8 *)&msg)[8] = (u8)(((u32)raw.y.value >> 16 & 0x7f) | ((u32)raw.y.value >> 24 & 0x80));
    ((u8 *)&msg)[9] = (u8)((u32)raw.y.value >> 8);
    ((u8 *)&msg)[10] = (u8)raw.y.value;
    raw.z = pPos->z;
    ((u8 *)&msg)[11] = (u8)(((u32)raw.z.value >> 16 & 0x7f) | ((u32)raw.z.value >> 24 & 0x80));
    ((u8 *)&msg)[12] = (u8)((u32)raw.z.value >> 8);
    ((u8 *)&msg)[13] = (u8)raw.z.value;

    if (*(int *)(st->pActor + 0x13c) - *(int *)(st->pActor + 0x80) > 0x100) {
        ((u8 *)&msg)[4] = 1;
    }

    pfnHook = *(void (**)(char *, struct Msg *, int))(st->pActor + 0x24);
    if (pfnHook != 0) {
        (*pfnHook)(st->pActor, &msg, 0xe);
    }
    func_ov107_020c9264(st->pActor, 3, 0);

    st->nField30 = 0;
    st->nField4c = 0;
    st->nField50 = 0;
    func_ov107_020c5af8(st->pActor, 0x153, 6, st->nParam44);
    func_0203c634(node, node->bSlot, (void *)func_ov164_020d1fd4);
}
