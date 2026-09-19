/* Start the ov246 leap: reseed the countdown from the owner's frame rate,
 * select animation two, build a Q12 velocity from the stored heading, then
 * install the per-frame leap handler. */
static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

static inline unsigned short FX_RadToIdx(int rad)
{
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

typedef struct Ov246MoveState {
    void *pOwner;
    unsigned char pad04[4];
    void *pTarget;
    int nHeading;
    int nTargetHeading;
    int nCountdown;
    unsigned char pad18[0x18];
    struct {
        int x;
        int y;
        int z;
    } vVelocity;
    int nPhaseTimer;
    int nProgress;
} Ov246MoveState;

typedef struct Ov246ActionNode {
    void *pOwner;
    Ov246MoveState *pState;
    void *apHandlers[6];
    signed char nHandlerSlot;
    unsigned char pad21[3];
} Ov246ActionNode;

extern void func_ov107_020c9264(void *owner, int anim, int flag);
extern void func_0203c634(int *node, unsigned short slot, int value);
extern void func_ov246_020d1018(Ov246ActionNode *node);
extern const short data_0203d210[];

void func_ov246_020d0edc(Ov246ActionNode *node)
{
    Ov246MoveState *state = node->pState;

    state->nCountdown = *(int *)((char *)node->pOwner + 0x2c) * 30 / 10;
    if (state->nProgress >= 0x200) {
        return;
    }
    func_ov107_020c9264(state->pOwner, 2, 0);
    state->vVelocity.x = FX_Mul(
        data_0203d210[(FX_RadToIdx(state->nHeading) >> 4) * 2], 0x300);
    state->vVelocity.y = 0x400;
    {
        int nCos = data_0203d210[(FX_RadToIdx(state->nHeading) >> 4) * 2 + 1];
        int nNextHandler = (int)func_ov246_020d1018;
        Ov246ActionNode *pNextNode = node;
        state->vVelocity.z = FX_Mul(nCos, 0x300);
        state->nPhaseTimer = 0;
        func_0203c634((int *)pNextNode, pNextNode->nHandlerSlot,
                      nNextHandler);
    }
}


