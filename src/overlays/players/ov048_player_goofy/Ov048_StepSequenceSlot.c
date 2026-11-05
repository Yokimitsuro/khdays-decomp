/* Steps one sequence slot of the ov048 enemy (x4: ov048/067/086/103). A slot in phase 2 whose
 * owner has left the attack modes (0x32/0x33) goes to phase 3: its sound handle is released and
 * tracks 0, 2 and 1 rebound to the slot's blend table with mode 1 (3 for the alternate slot).
 * Then per phase: 1 accumulates the timer, at 0x9000 (once, while +0x11c is clear) fires the
 * slot's action and tells 0x53 with the alternate flag, and at 0xc000 goes to phase 2; 2 just
 * advances the tracks; 3 advances them and goes idle when they finish. */

#include "game/engine.h"

extern void BindAnimTrack(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern unsigned short Sequence_UpdateTracks(void *animation, int delta);                            /* Sequence_UpdateTracks */
extern void Ov048_BindAnimsAndFaceOwner(char *self, char *slot);
extern void Ov022_PlayEntityVoice(char *self, int nSeqArc, int nSeq);

void Ov048_StepSequenceSlot(char *self, char *slot, int dt)
{
    int nBlend;

    if (*(int *)(slot + 8) == 2
        && *(int *)(self + 0x6bc) != 0x32 && *(int *)(self + 0x6bc) != 0x33) {
        *(int *)(slot + 8) = 3;
        nBlend = 1;
        if (*(int *)slot != 0) {
            nBlend = 3;
        }
        SoundSeqHandle_Stop(*(int *)(slot + 0x370));
        BindAnimTrack(slot + 0xc, 0, *(void **)(slot + 0x114), nBlend);
        BindAnimTrack(slot + 0xc, 2, *(void **)(slot + 0x114), nBlend);
        BindAnimTrack(slot + 0xc, 1, *(void **)(slot + 0x114), nBlend);
    }
    switch (*(int *)(slot + 8)) {
    case 1:
        *(int *)(slot + 0x118) += dt;
        if (*(int *)(slot + 0x118) >= 0x9000 && *(int *)(slot + 0x11c) == 0) {
            Ov048_BindAnimsAndFaceOwner(self, slot);
            Ov022_PlayEntityVoice(self, 0x53, *(int *)slot != 0 ? 1 : 0);
        }
        if (*(int *)(slot + 0x118) >= 0xc000) {
            *(int *)(slot + 8) = 2;
        }
        break;
    case 2:
        Sequence_UpdateTracks(slot + 0xc, dt);
        break;
    case 3:
        if (Sequence_UpdateTracks(slot + 0xc, dt) != 0) {
            *(int *)(slot + 8) = 0;
        }
        break;
    }
}
