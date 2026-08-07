typedef unsigned char u8;

struct State {
    char *pActor;
    char pad04[0x14];
    void *pTarget;      /* 0x18 */
    char pad1c[0xc];
    int nPhase28;       /* 0x28 */
    int nTimer2c;       /* 0x2c */
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void *func_ov107_020cab14(char *actor, int mode);
extern void func_ov107_020c9264(char *actor, int a, int b);
extern int func_02023eb4(int bound);
extern void func_0203c634(struct Node *node, int slot, void *next);

extern void func_ov285_020d23f0(void);

void func_ov285_020d2368(struct Node *node)
{
    struct State *st;
    void *pTarget;

    st = node->pState;
    pTarget = func_ov107_020cab14(st->pActor, 0);
    st->pTarget = pTarget;
    if (pTarget == 0) {
        *(u8 *)(st->pActor + 0x1c7) = 2;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    st->nPhase28 = 0;
    func_ov107_020c9264(st->pActor, 1, 1);
    st->nTimer2c = func_02023eb4(0x3001) + 0x1000;
    func_0203c634(node, node->bSlot, (void *)func_ov285_020d23f0);
}
