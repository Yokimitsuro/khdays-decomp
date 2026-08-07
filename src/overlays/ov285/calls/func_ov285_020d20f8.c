typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int nX;
    int nY;
    int nZ;
} VecFx32;

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct State {
    char *pActor;
    int nAngle04;
    int nAngleTarget08;
    char pad0c[4];
    VecFx32 *pPos10;
    char pad14[4];
    void *pTarget;      /* 0x18 */
    char pad1c[0xc];
    int nElapsed28;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern int func_020050b4(int x, int z);
extern void *func_ov107_020cab14(char *actor, int mode);
extern void func_ov107_020c9264(char *actor, int a, int b);
extern void func_0203c634(struct Node *node, int slot, void *next);

extern void func_ov285_020d21c8(void);

void func_ov285_020d20f8(struct Node *node)
{
    struct State *st;
    VecFx32 vToTarget;
    void *pTarget;
    int nElapsed;
    int nAngle;

    st = node->pState;
    nElapsed = st->nElapsed28 + *(int *)((char *)node->pScene + 0x2c);
    st->nElapsed28 = nElapsed;
    if (nElapsed < 0x6ee) {
        return;
    }

    pTarget = func_ov107_020cab14(st->pActor, 0);
    st->pTarget = pTarget;
    if (pTarget != 0) {
        VEC_Subtract((VecFx32 *)((char *)pTarget + 0x74), st->pPos10, &vToTarget);
        nAngle = func_020050b4(vToTarget.nX, vToTarget.nZ);
        st->nAngleTarget08 = nAngle;
        st->nAngle04 = nAngle;
    }

    ((struct Flags60 *)(st->pActor + 0x60))->hi =
        ((struct Flags60 *)(st->pActor + 0x60))->hi & ~0xc0;
    func_ov107_020c9264(st->pActor, 0, 0);
    st->nElapsed28 = 0;
    func_0203c634(node, node->bSlot, (void *)func_ov285_020d21c8);
}
