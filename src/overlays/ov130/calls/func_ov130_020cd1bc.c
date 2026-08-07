/* Spin-up tick. Accumulates scene time; once past 0x198 it seeds the spin
   speeds the first time through and then runs the decay every frame. It leaves
   the state as soon as the owner's busy byte at +0xad clears, kicking the actor
   into motion mode 5 and installing the next state. */

struct State {
    char *pActor;
    char *pOwner;
    char pad08[0x14];
    int nSpeed1c;
    char pad20[0xc];
    int nElapsed2c;
    int nSpin30;
    int nSpin34;
    char pad38[9];
    unsigned char bSeeded41;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void func_ov130_020cc468(struct Node *node);
extern void func_ov107_020c9264(char *actor, int a, int b);
extern void func_0203c634(struct Node *node, int slot, void *next);

extern void func_ov130_020cd248(void);

void func_ov130_020cd1bc(struct Node *node)
{
    struct State *st;
    int nElapsed;

    st = node->pState;
    nElapsed = st->nElapsed2c + *(int *)((char *)node->pScene + 0x2c);
    st->nElapsed2c = nElapsed;
    if (nElapsed >= 0x198) {
        if (st->bSeeded41 == 0) {
            st->nSpin30 = 0xc00;
            st->nSpeed1c = st->nSpin34 = 0x400;
            st->bSeeded41 = 1;
        }
        func_ov130_020cc468(node);
    }
    if (*(unsigned char *)(st->pOwner + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(st->pActor, 5, 1);
    func_0203c634(node, node->bSlot, (void *)func_ov130_020cd248);
}
