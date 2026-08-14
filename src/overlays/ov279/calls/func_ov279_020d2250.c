/*
 * ov272 orbit node: the wind-up tick that fires the orbit once its wait timer fills.
 *
 * Each tick adds the scene's frame delta to the node's wait timer. Below 0x1000 the
 * node is still winding up and nothing else happens. On reaching 0x1000 the timer is
 * reset, the orbit is aimed at a fixed start angle (0xffff6216) with a radius of
 * 0x2000 plus a random amount, and the node hands itself to the next state through the
 * shared 0203c634 resolve.
 *
 * The `else { return; }` is load-bearing, not a stylistic choice. Written the other way
 * round -- `if (sum < 0x1000) { return; }` followed by the body -- mwcc pulls the
 * literal-pool load forward and the output diverges at 0x28/0x2c. Keeping the body
 * inside the conditional region and the early exit in the else keeps the load where the
 * ROM has it. This is the same conditional-region-versus-early-exit lever documented in
 * the codegen notes, and here it is the ONLY thing that separates a match from a miss.
 */
struct Owner {
    char pad00[0x2c];
    int nFrameDelta;            /* 0x2c */
};

struct OrbitNode {
    char pad00[0x50];
    int nWaitTimer;             /* 0x50 */
    char pad54[0x10];
    int nOrbitAngle;            /* 0x64 */
    int nOrbitRadius;           /* 0x68 */
};

struct AiStateNode {
    struct Owner *pScene;       /* 0x00 */
    struct OrbitNode *pState;   /* 0x04 */
    char pad08[0x18];
    signed char bSlot;          /* 0x20 */
};

extern int func_02023eb4();
extern void func_0203c634(struct AiStateNode *self, int idx, void *cb);
extern void func_ov279_020d22b4(void);

void func_ov279_020d2250(struct AiStateNode *self)
{
    struct OrbitNode *node = self->pState;
    int sum;

    sum = node->nWaitTimer + self->pScene->nFrameDelta;
    node->nWaitTimer = sum;

    if (sum >= 0x1000) {
        node->nWaitTimer = 0;
        node->nOrbitAngle = 0xffff6216;
        node->nOrbitRadius = func_02023eb4(0x1001) + 0x2000;
        func_0203c634(self, self->bSlot, &func_ov279_020d22b4);
    } else {
        return;
    }
}
