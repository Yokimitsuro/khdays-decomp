/*
 * Ov002_StartCaptionVoice - start the voice line that goes with the caption.
 *
 * Nothing happens until the fade tween has finished. Any line still playing is
 * stopped first, then the new one is started: mode 2 walks its own sequence of
 * takes, one per call, wrapping the whole sequence away once it runs out, while
 * every other mode plays the single line its argument names.
 *
 * A chime is layered on top when the caption asks for one, and the caption is
 * left in state 2.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int pad0 : 2;
    unsigned int bDone : 1;
} Ov002Tween;

typedef struct {
    int hVoice;
    char pad004[4];
    int nState;
    int nLine;
    char pad010[0x48];
    Ov002Tween tweenFade;
    char pad074[0xc];
    int nVoiceArg;
    char pad084[0x14];
    int bChime;
    char pad09c[0x138];
    signed char aTake[8];
    u16 nTakeIndex;
    u16 nTakeCount;
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern const int data_ov002_0207ebf4[];

extern int func_02023930(int nSound, int nArg);
extern void WM_EndKeySharing_0x02023ad0(int hVoice);

extern void func_ov002_020536a0(void);
extern void func_ov002_02053558(int nSound);
extern void func_ov002_020535a4(void);

void func_ov002_02062a04(void)
{
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s->tweenFade.bDone == 0) {
        return;
    }

    func_ov002_020536a0();
    if (s->hVoice != 0) {
        WM_EndKeySharing_0x02023ad0(s->hVoice);
    }

    if (s->nLine == 2) {
        s->hVoice = func_02023930(data_ov002_0207ebf4[s->nLine],
                                  s->aTake[s->nTakeIndex]);
        s->nTakeIndex++;
        if (s->nTakeIndex >= s->nTakeCount) {
            s->nTakeCount = 0;
            s->nTakeIndex = 0;
        }
    } else {
        s->hVoice = func_02023930(data_ov002_0207ebf4[s->nLine],
                                  s->nVoiceArg);
    }

    if (s->bChime != 0) {
        func_ov002_02053558(0x3e9);
        func_ov002_020535a4();
    }
    s->nState = 2;
}
