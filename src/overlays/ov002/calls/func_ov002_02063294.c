/*
 * Ov002_ShowNoticeText - put a notice on the second caption surface.
 *
 * Only the first notice is taken: once a copy is held, later calls do nothing at
 * all. The line is copied onto the heap, drawn into the surface, and its extent
 * is kept for the layout that follows.
 *
 * During a replay the recap line is refreshed as well, and every accepted call
 * ends by kicking the step that puts the surface on screen.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[0xb8];
    u16 *pLine;
    char pad0bc[0x40];
    char noticeCtx[0x3c];
    char gaugeCtx[0x3c];
    int nExtent;
    int nRecap;
} Ov002CaptionScene;

extern int data_ov002_0207f62c;
extern u8 data_0204c240;

extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int nSize);
extern int func_020200c8(const u16 *pText);
extern void func_020200e4(u16 *pDst, const u16 *pSrc);
extern void func_02030278(void *pCtx, int a, int b, int c, const void *pText,
                          int d);
extern int func_020303b4(void *pCtx);

extern void func_ov002_02061f5c(void);
extern void func_ov002_02063398(void);

void func_ov002_02063294(const u16 *pText)
{
    Ov002CaptionScene *s;

    s = *(Ov002CaptionScene **)((char *)&data_ov002_0207f62c + 4);
    if (s->pLine != 0) {
        return;
    }

    if (pText != 0) {
        s->pLine =
            (u16 *)NNSi_FndAllocFromDefaultExpHeap((func_020200c8(pText) + 1) * 2);
        func_020200e4(s->pLine, pText);
        func_02030278(s->noticeCtx, 0, 0, 0xf, pText, 0);
        s->nExtent = func_020303b4(s->noticeCtx);
        if ((data_0204c240 & 6) == 2 && s->nRecap != 0) {
            func_ov002_02061f5c();
        }
    }
    func_ov002_02063398();
}
