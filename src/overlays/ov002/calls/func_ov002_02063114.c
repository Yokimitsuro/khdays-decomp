/*
 * Ov002_PlayCaptionCues - play or stop the four cues that go with a caption.
 *
 * The bits the mixer hands back say which of the four cues are wanted. Each one
 * is looked up in a table - the shared one, or the row of the line being shown -
 * and panned a little further left than the cue before it.
 *
 * The same walk both starts and stops them, which is what the second argument
 * picks.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    char pad000[0xc];
    int nLine;
} Ov002CaptionScene;

extern int data_ov002_0207f62c;
extern const u16 data_ov002_0207e360[];
extern const u16 data_ov002_0207e388[];

extern int func_ov002_02057420(void);
extern int func_ov002_02053558(int nCue);
extern int func_ov002_02053578(int nHandle, short nPan, short nColour);
extern void func_ov002_020535a4(int nHandle);
extern void func_ov002_020535f0(int nHandle);

void func_ov002_02063114(int bPerLine, int bStart)
{
    Ov002CaptionScene *s;
    const u16 *pCues;
    int i;
    int nPan;
    int nHandle;
    int nMask;

    s = *(Ov002CaptionScene **)((char *)&data_ov002_0207f62c + 4);
    nPan = 0x1e;
    nMask = func_ov002_02057420();
    if (nMask == 0) {
        return;
    }

    if (bPerLine != 0) {
        pCues = &data_ov002_0207e388[s->nLine * 4];
    } else {
        pCues = data_ov002_0207e360;
    }

    for (i = 3; i >= 0; i--) {
        if ((nMask & (1 << i)) != 0) {
            nHandle = func_ov002_02053558(pCues[i]);
            func_ov002_02053578(nHandle, (short)nPan, 0);
            if (bStart != 0) {
                func_ov002_020535a4(nHandle);
            } else {
                func_ov002_020535f0(nHandle);
            }
            nPan -= 2;
        }
    }
}
