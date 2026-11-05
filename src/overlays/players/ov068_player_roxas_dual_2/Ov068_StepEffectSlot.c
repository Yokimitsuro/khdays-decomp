/* Steps one effect slot of the ov049 enemy (x4: ov049/068/087/104). A slot in phase 3 whose
 * owner lost the local flag bit 16 or left modes 0x2f/0x30 rebinds its tracks in mode 3,
 * releases its sound handle and goes to phase 5; a slot in phase 6 goes idle once the emitter
 * at +0x22f8 is quiet. Phase 1 waits for the +0x7b0 timer to reach 0x9000, then starts sound
 * 0xd2 (variant and scale by the slot's alternate flag), binds and rewinds tracks 0 and 2 and
 * goes to phase 2; 2 advances and, when done, rebinds in mode 2 (1 without the flag) into
 * phase 3; 3 only advances; 4 advances and on completion releases the sound into phase 1; 5
 * advances into phase 6. */

#include "game/engine.h"

extern void BindAnimTrack(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void Anim_SetFrameWrapped(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern unsigned short Sequence_UpdateTracks(void *animation, int delta);                            /* Sequence_UpdateTracks */
extern int Ov022_IsState9Or6WithFlag200(char *emitter);
extern int Ov022_PlayEntityVoice(char *self, int nSeqArc, int nSeq);

void Ov068_StepEffectSlot(char *self, char *slot, int dt)
{
    int scale;
    int variant;
    int nBlend;

    if (*(signed char *)slot == 3
        && ((*(unsigned long long *)(self + 0x464) & 0x10000) == 0
            || (*(int *)(self + 0x6bc) != 0x2f && *(int *)(self + 0x6bc) != 0x30))) {
        BindAnimTrack(slot + 4, 0, *(void **)(slot + 0x10c), 3);
        BindAnimTrack(slot + 4, 2, *(void **)(slot + 0x10c), 3);
        if (*(int *)(slot + 0x120) != 0) {
            SoundSeqHandle_Stop(*(int *)(slot + 0x120));
        }
        *(int *)(slot + 0x120) = 0;
        *slot = 5;
    }
    if (*(signed char *)slot == 6 && (*(unsigned long long *)(self + 0x464) & 0x10000) == 0
        && Ov022_IsState9Or6WithFlag200(self + 0x2f8 + 0x2000) == 0) {
        *slot = 0;
    }
    switch (*(signed char *)slot) {
    case 1:
        if (*(int *)(self + 0x7b0) < 0x9000) {
            return;
        }
        if (*(int *)(slot + 0x118) != 0) {
            scale = 0x1000;
            variant = 1;
        } else {
            scale = 0x99a;
            variant = 0;
        }
        *(int *)(slot + 0x120) = Ov022_PlayEntityVoice(self, 0xd2, variant);
        *(int *)(slot + 0xbc) = scale;
        *(int *)(slot + 0xb8) = scale;
        *(int *)(slot + 0xb4) = scale;
        BindAnimTrack(slot + 4, 0, *(void **)(slot + 0x10c), 0);
        BindAnimTrack(slot + 4, 2, *(void **)(slot + 0x10c), 0);
        Anim_SetFrameWrapped(slot + 4, 0, 0);
        Anim_SetFrameWrapped(slot + 4, 2, 0);
        *slot = 2;
        break;
    case 2:
        if (Sequence_UpdateTracks(slot + 4, dt) != 0) {
            nBlend = *(int *)(slot + 0x118) != 0 ? 2 : 1;
            BindAnimTrack(slot + 4, 0, *(void **)(slot + 0x10c), nBlend);
            BindAnimTrack(slot + 4, 2, *(void **)(slot + 0x10c), nBlend);
            *slot = 3;
        }
        break;
    case 3:
        Sequence_UpdateTracks(slot + 4, dt);
        break;
    case 4:
        if (Sequence_UpdateTracks(slot + 4, dt) != 0) {
            if (*(int *)(slot + 0x120) != 0) {
                SoundSeqHandle_Stop(*(int *)(slot + 0x120));
            }
            *(int *)(slot + 0x120) = 0;
            *slot = 1;
        }
        break;
    case 5:
        if (Sequence_UpdateTracks(slot + 4, dt) != 0) {
            *slot = 6;
        }
        break;
    }
}
