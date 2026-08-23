/*
 * Ov002_SceneOpenPanelSurface - hand the panel's tile block to the hardware and
 * bring the surface it draws into up, once.
 *
 * The node's resource is looked up, its character block queued to VRAM and its
 * palette queued behind it, and the node itself released - none of which depends
 * on the surface existing yet. The surface is only built the first time: the two
 * scratch buffers are claimed, the four words the scene set aside describe it,
 * and the optional source at +0x68c+4 is passed only when the word at +0x68c
 * says there is one. The scene then moves to state 2 and arms its next step.
 *
 * THUMB.
 */

typedef unsigned char u8;

typedef struct {
    int aRect[4];                       /* +0x668 */
    u8 pad0678[0x14];
    int nHasSource;                     /* +0x68c */
    int aSource[1];                     /* +0x690 */
} Ov002SurfaceParams;

typedef struct {
    int nState;                         /* +0x000 */
    u8 pad0004[4];
    int *pTileSet;                      /* +0x008 */
    u8 pad000c[4];
} Ov002SceneContext;

extern Ov002SceneContext *data_ov002_0207f624;

extern void func_02011988(unsigned int nResource, int *pBlock);
extern void GFXi_EnqueueCommand(int nKind, int nSize, int nSource, int nDest);
extern void func_02023a44(int nObject, void *pStep);

extern unsigned int func_ov002_02052aec(void *pNode);
extern void func_ov002_02052af4(void *pNode, int nValue);
extern void func_ov002_02052368(void *pSurface, int nKind, int nSize, int a0,
                                int a1, int a2, int a3, int nBufferA,
                                int nBufferB, void *pSource, int nLast);
extern void func_ov002_020539f4(int nKey);
extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02053d28(int nKind, int nSize, int nSource, int nDest,
                                unsigned int nResource);
extern void func_ov002_0205ef18(void);

void func_ov002_0205e4f0(void *pNode)
{
    Ov002SceneContext *ctx;
    Ov002SurfaceParams *p;
    void *pSource;
    unsigned int nResource;
    int nBlock;
    int nBufferA;
    int nBufferB;

    ctx = data_ov002_0207f624;
    p = (Ov002SurfaceParams *)((char *)ctx + 0x668);
    nResource = func_ov002_02052aec(pNode);
    func_02011988(nResource, &nBlock);
    func_ov002_02053d28(7, 0x4c00, *(int *)(nBlock + 0x14),
                        *(int *)(nBlock + 0x10), nResource);
    GFXi_EnqueueCommand(0xf, 0x180, ctx->pTileSet[3], 0x20);
    func_ov002_02052af4(pNode, 0);

    if (*(int *)((char *)ctx + 0x660) == 0) {
        func_ov002_020539f4(*(int *)((char *)ctx + 0x69c));
        if (p->nHasSource == 0) {
            pSource = 0;
        } else {
            pSource = p->aSource;
        }
        nBufferA = func_ov002_02053bb8(0xb);
        nBufferB = func_ov002_02053bb8(10);
        func_ov002_02052368((char *)ctx + 0xc, 3, 0x260, p->aRect[0], p->aRect[1],
                            p->aRect[2], p->aRect[3], nBufferA, nBufferB, pSource,
                            0xc);
        func_ov002_020539f4(*(int *)((char *)ctx + 0x6a0));
        *(int *)((char *)ctx + 0x660) = 1;
    }

    ctx->nState = 2;
    func_02023a44(*(int *)((char *)ctx + 0x6a4), func_ov002_0205ef18);
}
