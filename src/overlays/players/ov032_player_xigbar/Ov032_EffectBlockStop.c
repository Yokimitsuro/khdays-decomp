/* Stops the ov032 enemy's effect block (and its byte-identical twins) from states 1/2: enters
 * state 4, fires cue 0xc5 with situation 0 (index 1) or 1 (index 2) by `alt`, retimes sequences
 * 0, 2 and 1 against the owner's +0x22f8 period with that index and restarts them from zero. */

#include "nitro/types.h"

extern void Ov022_PlayEntityVoice(int self, int nSeqArc, int nSeq);
extern int Ov022_GetWordAt0x348Plus4(void *p);
extern void BindAnimTrack(void *p, u16 idx, int a, short b);
extern void Anim_SetFrameWrapped(void *p, int idx, int a);

void Ov032_EffectBlockStop(int self, u8 *block, int alt)
{
    int idx;

    if ((u8)(block[0x114] + 0xff) > 1) {
        return;
    }
    block[0x114] = 4;
    if (alt == 0) {
        idx = 1;
        Ov022_PlayEntityVoice(self, 0xc5, 0);
    } else {
        idx = 2;
        Ov022_PlayEntityVoice(self, 0xc5, 1);
    }
    BindAnimTrack(block + 0xc, 0, Ov022_GetWordAt0x348Plus4((void *)(self + 0x22f8)), idx);
    BindAnimTrack(block + 0xc, 2, Ov022_GetWordAt0x348Plus4((void *)(self + 0x22f8)), idx);
    BindAnimTrack(block + 0xc, 1, Ov022_GetWordAt0x348Plus4((void *)(self + 0x22f8)), idx);
    Anim_SetFrameWrapped(block + 0xc, 0, 0);
    Anim_SetFrameWrapped(block + 0xc, 2, 0);
    Anim_SetFrameWrapped(block + 0xc, 1, 0);
}
