/* Steps one sequence slot of the ov041 enemy (x4: ov041/060/080/097). Any slot that is not idle
 * is reset when the enemy leaves mode 0x2f. Phase 1 waits for the enemy's +0x7b0 timer to reach
 * 0x3000, then binds tracks 0 and 2 of the slot's animation to its own blend table (+0xe4),
 * rewinds both, goes to phase 2 and tells the enemy 0xd7; phase 2 advances the tracks and goes
 * back to phase 1 when they finish -- or, still running, when the enemy is in mode 0x2f with
 * the timer below 0x3000 again. */
typedef short s16;

extern void func_0202accc(void *animation, int track, void *table, s16 mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern int func_0202a818(void *animation, int delta);                          /* Sequence_UpdateTracks */
extern void func_ov022_020a4490(char *self, int nSound, int nVariant);

void func_ov097_020bb224(char *self, char *slot, int dt)
{
    if (*(int *)(self + 0x6bc) != 0x2f && *(int *)slot != 0) {
        *(int *)slot = 0;
    }
    switch (*(int *)slot) {
    case 1:
        if (*(int *)(self + 0x6bc) == 0x2f) {
            if (*(int *)(self + 0x7b0) < 0x3000) {
                break;
            }
            func_0202accc(slot + 4, 0, slot + 0xe4, 0);
            func_0202accc(slot + 4, 2, slot + 0xe4, 0);
            func_01fff774(slot + 4, 0, 0);
            func_01fff774(slot + 4, 2, 0);
            *(int *)slot = 2;
            func_ov022_020a4490(self, 0xd7, 0);
        } else {
            *(int *)slot = 0;
        }
        break;
    case 2:
        if (func_0202a818(slot + 4, dt) != 0) {
            *(int *)slot = 1;
        } else if (*(int *)(self + 0x6bc) == 0x2f) {
            if (*(int *)(self + 0x7b0) < 0x3000) {
                *(int *)slot = 1;
            }
        }
        break;
    }
}
