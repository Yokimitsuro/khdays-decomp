typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Msg {
    u16 h[7];
};

struct W1 {
    int v;
};

struct Comp388 {
    char pad00[8];
    u32 bLow : 8;
};

struct State {
    char *pActor;
    char pad04[0x2c];
    int nField30;
    char pad34[0xc];
    VecFx32 *pPos40;
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
extern const struct Msg data_ov132_020d0dbe;
extern void func_ov132_020d00d4(void);

void func_ov132_020cff08(struct Node *node)
{
    struct State *st;
    struct Msg msg;
    VecFx32 raw;
    VecFx32 *pPos;
    u16 *hw;
    unsigned int h;
    void (*pfnHook)(char *, struct Msg *, int);

    st = node->pState;

    hw = (u16 *)(st->pActor + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((u32)h << 0x10) >> 0x18 | 0x46) << 0x18) >> 0x10);
    *(u16 *)(st->pActor + 0x1ae) |= 1;
    ((struct Comp388 *)*(void **)(st->pActor + 0x388))->bLow &= ~1;

    msg = data_ov132_020d0dbe;

    pPos = st->pPos40;
    *(struct W1 *)&raw.x = *(struct W1 *)&pPos->x;
    ((u8 *)&msg)[5] = (u8)(((u32)raw.x >> 16 & 0x7f) | ((u32)raw.x >> 24 & 0x80));
    ((u8 *)&msg)[6] = (u8)((u32)raw.x >> 8);
    ((u8 *)&msg)[7] = (u8)raw.x;
    *(struct W1 *)&raw.y = *(struct W1 *)&pPos->y;
    ((u8 *)&msg)[8] = (u8)(((u32)raw.y >> 16 & 0x7f) | ((u32)raw.y >> 24 & 0x80));
    ((u8 *)&msg)[9] = (u8)((u32)raw.y >> 8);
    ((u8 *)&msg)[10] = (u8)raw.y;
    *(struct W1 *)&raw.z = *(struct W1 *)&pPos->z;
    ((u8 *)&msg)[11] = (u8)(((u32)raw.z >> 16 & 0x7f) | ((u32)raw.z >> 24 & 0x80));
    ((u8 *)&msg)[12] = (u8)((u32)raw.z >> 8);
    ((u8 *)&msg)[13] = (u8)raw.z;

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
    *(u8 *)(st->pActor + 0x1c5) &= ~0xf;
    func_ov107_020c5af8(st->pActor, 0x119, 6, st->nParam44);
    func_0203c634(node, node->bSlot, (void *)func_ov132_020d00d4);
}
