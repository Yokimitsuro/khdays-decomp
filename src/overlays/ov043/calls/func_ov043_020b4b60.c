/* Rebinds the enemy's five animation tracks: any animation object still attached to a track
 * is removed from the render object at +0x30 and its slot at +0x1c cleared, then every track is
 * bound to the blend table at +0x118 with the given mode and rewound to frame 0. */
typedef unsigned short u16;
typedef short s16;

extern void func_02014dc4(void *renderObj, void *anmObj);                    /* NNS_G3dRenderObjRemoveAnmObj */
extern void func_0202accc(void *animation, u16 track, void *table, s16 mode); /* BindAnimTrack */
extern void func_01fff774(void *animation, u16 track, int frame);             /* Anim_SetFrameWrapped */

void func_ov043_020b4b60(char *self, int mode)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (((void **)(self + 0x1c))[i] != 0) {
            func_02014dc4(self + 0x30, (void *)((void **)(self + 0x1c))[i]);
            *(void **)(self + i * sizeof(void *) + 0x1c) = 0;
        }
        func_0202accc(self + 0x10, (u16)i, *(void **)(self + 0x118), mode);
        func_01fff774(self + 0x10, (u16)i, 0);
    }
}
