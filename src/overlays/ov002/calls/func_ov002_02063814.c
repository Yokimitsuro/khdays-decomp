/*
 * Ov002_UploadCaptionChars - push the caption surface's characters to the sub BG.
 *
 * Nothing is uploaded until the surface exists and has been built. The caller
 * says whether the plain item is wanted; the styled one is used only when it is
 * not asked to be skipped and the screen actually has a style.
 *
 * Returns 1 once the upload has been queued, 0 while there is nothing to send.
 *
 * ARM.
 */

typedef struct {
    char pad000[0x20];
    const void *pChar;
} Ov002CharSource;

typedef struct {
    char pad000[0xc];
    unsigned int nSize;
    unsigned int nOffset;
    char pad014[4];
    Ov002CharSource *pSource;
    char pad01c[0x20];
} Ov002TextSurface;

typedef struct {
    char pad000[0x10];
    Ov002TextSurface surf;
    int nLoaded;
    int nBaseItem;
    int nStyle;
} Ov002CaptionScene;

extern int data_ov002_0207f62c;

extern void GXS_LoadBG0Char(const void *pSrc, unsigned int nOffset,
                            unsigned int nSize);
extern void func_02030094(void *pCtx, int nItem, int nFlags);

int func_ov002_02063814(int bPlain)
{
    Ov002CaptionScene *s;

    s = *(Ov002CaptionScene **)((char *)&data_ov002_0207f62c + 4);
    if (s == 0 || s->nLoaded == 0) {
        return 0;
    }

    if (bPlain != 0 || s->nStyle == 0) {
        func_02030094(&s->surf, s->nBaseItem, 0);
    } else {
        func_02030094(&s->surf, s->nStyle, 0);
    }

    GXS_LoadBG0Char(s->surf.pSource->pChar, s->surf.nOffset, s->surf.nSize);
    return 1;
}
