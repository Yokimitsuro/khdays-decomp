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

#include "nitro/types.h"

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

extern int InstantiateClass(int nSound, int nArg);
extern void VeneerTo_Obj_Destroy(int hVoice);

extern void Ov002_ClearWorldElements(void);
extern int Ov002_ForwardToSubDc(int nSound);
extern void Ov002_Ctx_InvokeTagTrackerCallback(int);

void Ov002_StartCaptionVoice(void)
{
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s->tweenFade.bDone == 0) {
        return;
    }

    Ov002_ClearWorldElements();
    if (s->hVoice != 0) {
        VeneerTo_Obj_Destroy(s->hVoice);
    }

    if (s->nLine == 2) {
        s->hVoice = InstantiateClass(data_ov002_0207ebf4[s->nLine],
                                  s->aTake[s->nTakeIndex]);
        s->nTakeIndex++;
        if (s->nTakeIndex >= s->nTakeCount) {
            s->nTakeCount = 0;
            s->nTakeIndex = 0;
        }
    } else {
        s->hVoice = InstantiateClass(data_ov002_0207ebf4[s->nLine],
                                  s->nVoiceArg);
    }

    if (s->bChime != 0) {
        Ov002_Ctx_InvokeTagTrackerCallback(Ov002_ForwardToSubDc(0x3e9));
    }
    s->nState = 2;
}
