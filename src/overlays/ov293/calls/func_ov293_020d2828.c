typedef unsigned char u8;

struct State {
    char *pActor;       /* 0x00 */
    void *pTarget;       /* 0x04 */
    char pad08[0x10];
    int field_18;         /* 0x18 */
    char pad1c[0x24];
    int field_40;         /* 0x40 */
    int nTimer44;          /* 0x44 */
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void *func_ov107_020cab14(char *actor, int mode);
extern void func_ov107_020c9264(char *actor, int mode, int b);
extern int func_02023eb4(int bound);
extern void func_0203c634(struct Node *node, int slot, void *next);

extern void func_ov293_020d28b4(void);

void func_ov293_020d2828(struct Node *node)
{
    struct State *st;
    void *pTarget;
    int mode;

    st = node->pState;
    mode = 2;
    pTarget = func_ov107_020cab14(st->pActor, 0);
    st->pTarget = pTarget;
    if (pTarget == 0) {
        st->field_18 = 0x2000;
        *(u8 *)(st->pActor + 0x1c7) = mode;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    st->field_40 = 0;
    func_ov107_020c9264(st->pActor, mode, 1);
    st->nTimer44 = func_02023eb4(0x5001) + 0x1000;
    func_0203c634(node, node->bSlot, (void *)func_ov293_020d28b4);
}
