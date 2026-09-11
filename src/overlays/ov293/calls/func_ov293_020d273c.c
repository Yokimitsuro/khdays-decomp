typedef unsigned char u8;

typedef struct State {
    char *pActor;          /* 0x00 */
    char *pTarget;         /* 0x04 */
    char pad08[0x0c];
    int nSpeed;            /* 0x14 */
    int nCheckInterval;    /* 0x18 */
    char pad1c[0x24];
    int nCheckTimer;       /* 0x40 */
} State;

typedef struct Scene {
    char pad00[0x2c];
    int nDelta;            /* 0x2c */
} Scene;

typedef struct Node {
    Scene *pScene;
    State *pState;
    char pad08[0x18];
    signed char bSlot;
} Node;

extern char *func_ov107_020cab14(char *actor, int *pDistSq);
extern int FX_Sqrt(int x);
extern void func_0203c634(Node *node, int slot, void *next);

extern int data_ov293_020d3660[];

void func_ov293_020d273c(Node *node)
{
    State *st;
    char *actor;
    char *target;
    int gap;

    st = node->pState;
    st->nSpeed = node->pScene->nDelta * 30 / 5;
    target = st->pTarget = func_ov107_020cab14(st->pActor, &gap);
    if (target == 0) {
        return;
    }

    actor = st->pActor;
    gap = FX_Sqrt(gap) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));

    if (data_ov293_020d3660[2] == 0) {
        st->nCheckTimer += node->pScene->nDelta;
        if (st->nCheckTimer < st->nCheckInterval) {
            return;
        }
        st->nCheckTimer = 0;
        *(u8 *)(st->pActor + 0x1c7) = 4;
        func_0203c634(node, node->bSlot, 0);
        return;
    }

    if (gap < 0x3000) {
        return;
    }
    *(u8 *)(st->pActor + 0x1c7) = 4;
    func_0203c634(node, node->bSlot, 0);
}
