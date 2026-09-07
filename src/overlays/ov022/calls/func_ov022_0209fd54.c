/* ov022: run the remote-replay branch of the actor's frame.
 *
 * Used when the actor is being replayed rather than simulated. It pauses the
 * node's animation, runs the pre-draw hook and the pending replay entry, forces
 * the node's angle and animation flags, drives the node once at the replay
 * step, then runs the post-draw hook and resumes the animation if the actor
 * still wants it.
 *
 * The two hooks sit either side of the node update, next to the general update
 * hook the subsystem dispatcher calls, so the actor carries three of them.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

struct Node {
    u32 nFlags;                   /* 0x00 */
    u16 nAnimFlags;               /* 0x04 */
    u8 pad06[0x7c];
    u16 nAngle;                   /* 0x82 */
    u8 pad84[0xc4];
    u32 nStep;                    /* 0x148 */
};

struct Actor;
typedef void (*PfnHook)(struct Actor *pActor);
typedef void (*PfnReplayHook)(struct Actor *pActor, int nIndex);

struct Actor {
    u8 pad000[0x20];
    struct Node *pNode;           /* 0x020 */
    u8 pad024[0x4e4];
    int nReplayIndex;             /* 0x508 */
    int nReplayArg;               /* 0x50c */
    u16 nReplayAngle;             /* 0x510 */
    u8 pad512[0x152];
    PfnReplayHook pfnPreDraw;     /* 0x664 */
    PfnHook pfnPostDraw;          /* 0x668 */
};

extern void func_0202af2c(u16 *pAnim);
extern void func_ov022_02097038(struct Actor *pActor, int nArg);
extern void func_0202da08(struct Node **ppNode, struct Vec3 *pOut, int nMode);
extern int func_ov022_020ad588(struct Actor *pActor);
extern void func_0202af1c(u16 *pAnim);

int func_ov022_0209fd54(struct Actor *pActor)
{
    struct Node *pNode;
    PfnReplayHook pfnHook;
    int nIndex;
    struct Vec3 vecTmp;

    if ((pActor->pNode->nFlags & 0x20) == 0) {
        func_0202af2c(&pActor->pNode->nAnimFlags);
    }
    nIndex = pActor->nReplayIndex;
    if (nIndex >= 0) {
        pfnHook = pActor->pfnPreDraw;
        pfnHook(pActor, nIndex);
        func_ov022_02097038(pActor, pActor->nReplayArg);
    }
    pNode = pActor->pNode;
    pNode->nAngle = pActor->nReplayAngle;
    pNode->nAnimFlags |= 0x20;
    pActor->pNode->nStep = 0xd00;
    func_0202da08(&pActor->pNode, &vecTmp, 1);
    pActor->pNode->nStep = 0x900;
    pActor->pfnPostDraw(pActor);
    if (func_ov022_020ad588(pActor) != 0
        && (pActor->pNode->nFlags & 0x20) == 0) {
        func_0202af1c(&pActor->pNode->nAnimFlags);
    }
    return 0;
}
