/* Step one of this enemy's sequence slots (state at +0, animation at +4, timers at +0x110 /
 * +0x114, blend table at +0x10c): in state 1 the wait timer counts up to its limit, then cue
 * 0xce plays (variant 1 while the shared rig's +0x2c50 flag is set, 0 otherwise -- the same value
 * picks the blend mode), tracks 0 and 2 are bound to the blend table and rewound, and the slot
 * enters state 2; in state 2 the timer keeps counting while the tracks play, and the slot goes
 * idle when they finish. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

extern void func_ov022_020a4490(char *self, int nSound, int nVariant);
extern void func_0202accc(void *animation, int track, void *table, s16 mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern int func_0202a818(void *animation, int delta);                          /* Sequence_UpdateTracks */
extern char *data_ov096_020bc0c0;

void func_ov096_020baff4(char *self, char *slot, int dt)
{
    char *rig = data_ov096_020bc0c0 + 0x2c50;
    int mode;

    switch (*(int *)slot) {
    case 1:
        *(int *)(slot + 0x110) += dt;
        if (*(int *)(slot + 0x110) < *(int *)(slot + 0x114)) {
            return;
        }
        if (*(int *)rig == 0) {
            mode = 0;
            func_ov022_020a4490(self, 0xce, mode);
        } else {
            mode = 1;
            func_ov022_020a4490(self, 0xce, mode);
        }
        func_0202accc(slot + 4, 0, *(void **)(slot + 0x10c), (s16)mode);
        func_0202accc(slot + 4, 2, *(void **)(slot + 0x10c), (s16)mode);
        func_01fff774(slot + 4, 0, 0);
        func_01fff774(slot + 4, 2, 0);
        *(int *)slot = 2;
        *(int *)(slot + 0x110) = 0;
        break;
    case 2:
        *(int *)(slot + 0x110) += dt;
        if (func_0202a818(slot + 4, dt) != 0) {
            *(int *)slot = 0;
        }
        break;
    }
}
