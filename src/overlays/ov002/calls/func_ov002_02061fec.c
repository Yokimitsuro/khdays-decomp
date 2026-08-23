/*
 * Ov002_DrawLoadedPortrait - finish a portrait load and put the caption under
 * it.
 *
 * Without a live text context the load node is thrown away. Otherwise what was
 * loaded is copied into the context's tile buffer: the wide layout copies two
 * 0x140-byte halves and captions itself from message 9, the narrow one copies a
 * single block whose size the context carries and captions itself from whatever
 * 0206333c hands back.
 *
 * In the narrow case the second screen also gets its own surface and the same
 * block, and the message caption is drawn there.
 *
 * THUMB.
 */

typedef struct {
    char pad000[0xfc];
    char textCtx[0xc];
    int nCopySize;
    char pad10c[8];
    void *pTiles;
    char pad118[0x60];
    void *pSurface;
    char pad17c[0x38];
    char msgCtx[0x40];
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern int data_0204c240;

extern void func_02011988(int nId, void **ppOut);
extern void MIi_CpuCopyFast(const void *pSrc, void *pDst, unsigned int nSize);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern int func_020235d0(int a, int b);
extern void *func_0202fff8(void *pCtx, int nFlags);
extern void func_02030278(void *pCtx, int a, int b, int c, void *pText, int d);

extern void func_ov002_02052af4(void *pNode, int nMode);
extern void func_ov002_0205287c(void *pMsg, int nKind, char *pOut, int nSize,
                                int nEntry);
extern int func_ov002_020575d0(void);
extern void *func_ov002_0206333c(void);
extern void func_ov002_02061f5c(void);
extern void func_ov002_02063398(void);

void func_ov002_02061fec(void *pNode)
{
    void *pText;
    void *pSub;
    char aText[0x20];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s == 0) {
        func_ov002_02052af4(pNode, 1);
        return;
    }

    func_02011988(*(int *)((char *)pNode + 8), &pSub);
    if (func_ov002_020575d0() != 0) {
        MIi_CpuCopyFast(*(void **)((char *)pSub + 0x14),
                        *(void **)((char *)s->pTiles + 0x20), 0x140);
        MIi_CpuCopyFast((char *)*(void **)((char *)pSub + 0x14) + 0x320,
                        (char *)*(void **)((char *)s->pTiles + 0x20) + 0x140,
                        0x140);
        func_ov002_0205287c(s->msgCtx, 0, aText, 0x10, func_020235d0(0, 9));
        func_02030278(s->textCtx, 0, 0, 0xf, aText, 0);
    } else {
        MI_CpuCopy8(*(void **)((char *)pSub + 0x14),
                    *(void **)((char *)s->pTiles + 0x20), s->nCopySize);
        pText = func_ov002_0206333c();
        if ((*(unsigned char *)&data_0204c240 & 6) == 2) {
            s->pSurface = func_0202fff8(s->textCtx, 0);
            MI_CpuCopy8(*(void **)((char *)pSub + 0x14),
                        *(void **)((char *)s->pSurface + 0x20), s->nCopySize);
            func_ov002_02061f5c();
        }
        if (pText != 0) {
            func_02030278(s->textCtx, 0, 0, 0xf, pText, 0);
        }
    }

    func_ov002_02052af4(pNode, 1);
    func_ov002_02063398();
}
