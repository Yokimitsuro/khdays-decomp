/*
 * Ov002_SetCaptionText - put a line of text on the caption surface.
 *
 * The first line asked for brings the surface up: its two resources are handed
 * to the shared text globals, the surface is built, the top rows of the BG1
 * screen are refreshed, and during a replay the run summary is built once.
 *
 * Every line is then drawn with the surface temporarily switched to item 0, and
 * its width is kept both for the row that owns it and for the next caller.
 *
 * A null line only clears what is there, and either way the surface is flushed
 * before the caption entry is selected again.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[0x10];
    char textCtx[0x3c];
    int bLoaded;
    int nBaseItem;
    int nStyle;
    char pad058[0x58];
    int nWidth;
} Ov002CaptionScene;

extern int data_ov002_0207f62c;
extern int data_ov002_0207ebf4[];
extern const int data_ov002_0207ec28;
extern u8 data_0204c240;

extern void *G2S_GetBG1ScrPtr(void);
extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);

extern void func_0202ff8c(void *pCtx, const void *pCfg);
extern int func_0202fff8(void *pCtx, int nIndex);
extern void func_02030094(void *pCtx, int nStyle, int nFlags);
extern void func_020300f8(void *pCtx);
extern void func_02030158(void *pCtx);
extern void func_02030278(void *pCtx, int a, int b, int c, const void *pText,
                          int d);
extern int func_020303b4(void *pCtx);
extern int func_020303bc(void *pCtx, const void *pText);

extern int func_ov002_02053bb8(int nId);
extern void func_ov002_02053cd4(int nId);
extern int func_ov002_0205740c(void);
extern void func_ov002_02057454(int nRow, int nWidth);
extern void func_ov002_02062748(void);

void func_ov002_02062f6c(const u16 *pText)
{
    Ov002CaptionScene *s;
    int nItem;
    char *pScreen;

    s = *(Ov002CaptionScene **)((char *)&data_ov002_0207f62c + 4);
    if (pText != 0) {
        if (s->bLoaded == 0) {
            data_ov002_0207ebf4[0x13] = func_ov002_02053bb8(0x18);
            data_ov002_0207ebf4[0x15] = func_ov002_0205740c();
            func_0202ff8c(s->textCtx, &data_ov002_0207ec28);
            pScreen = (char *)G2S_GetBG1ScrPtr();
            MIi_CpuCopy16(pScreen + 0x700,
                          (char *)func_ov002_02053bb8(0x19) + 0x700, 0x80);
            func_ov002_02053cd4(0x19);
            s->nBaseItem = func_020303b4(s->textCtx);
            if ((data_0204c240 & 6) == 2) {
                s->nStyle = func_0202fff8(s->textCtx, 0);
                func_ov002_02062748();
            }
            s->bLoaded = 1;
        }
        nItem = func_020303b4(s->textCtx);
        func_02030094(s->textCtx, 0, 0);
        func_02030158(s->textCtx);
        func_02030278(s->textCtx, 8, 3, 2, pText, 0);
        s->nWidth = func_020303bc(s->textCtx, pText);
        func_ov002_02057454(0, s->nWidth);
        func_02030094(s->textCtx, nItem, 0);
    } else {
        if (s->bLoaded != 0) {
            nItem = func_020303b4(s->textCtx);
            func_02030094(s->textCtx, 0, 0);
            func_02030158(s->textCtx);
            func_02030094(s->textCtx, nItem, 0);
        }
        s->nWidth = 0;
    }
    func_020300f8(s->textCtx);
    func_ov002_02053cd4(0x18);
}
