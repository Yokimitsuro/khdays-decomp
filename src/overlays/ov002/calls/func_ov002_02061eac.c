/*
 * Ov002_DrawLoadedCaption - finish a caption load and draw the line.
 *
 * Without a live text context the load node is simply thrown away. Otherwise
 * the character block that was loaded is copied into the context's target and
 * the node is released.
 *
 * The caption text is then measured with the context's own font; anything wider
 * than 0x78 is drawn with the narrow font instead, which is bound just for the
 * one line and put back afterwards. The line is drawn with its shadow, and the
 * scene's pending queue is drained on the way out.
 *
 * THUMB.
 */

typedef struct {
    char pad000[0xc0];
    char textCtx[0xc];
    unsigned int nSize;
    char pad0d0[8];
    void *pTarget;
    char pad0dc[4];
    int nFont;
    int nFontAlt;
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern const char data_ov002_0207ecb4[];

extern void func_02011988(int nId, void **ppOut);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void func_0202ff58(void *pFont, const char *pName);
extern void func_0202ff7c(void *pFont);
extern int func_02013768(int nFont, int nFontAlt, void *pText, int *pOut);
extern void func_02030278(void *pCtx, int a, int b, int c, void *pText, int d);

extern void func_ov002_02052af4(void *pNode, int nMode);
extern void *func_ov002_0206325c(void);
extern int func_ov002_0205740c(void);
extern void func_ov002_02063270(void);

void func_ov002_02061eac(void *pNode)
{
    int bWide;
    void *pSub;
    char aFont[0xc];
    void *pText;
    int nFont;
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s == 0) {
        func_ov002_02052af4(pNode, 1);
        return;
    }

    func_02011988(*(int *)((char *)pNode + 8), &pSub);
    MI_CpuCopy8(*(void **)((char *)pSub + 0x14),
                *(void **)((char *)s->pTarget + 0x20), s->nSize);
    func_ov002_02052af4(pNode, 1);

    pText = func_ov002_0206325c();
    if (pText != 0) {
        func_0202ff58(aFont, data_ov002_0207ecb4);
        nFont = func_ov002_0205740c();
        bWide = func_02013768(s->nFont, s->nFontAlt, pText, 0) > 0x78;
        if (bWide != 0) {
            s->nFont = (int)aFont;
        }
        func_02030278(s->textCtx, 0, 2, 2, pText, 1);
        if (bWide != 0) {
            s->nFont = nFont;
        }
        func_0202ff7c(aFont);
    }
    func_ov002_02063270();
}
