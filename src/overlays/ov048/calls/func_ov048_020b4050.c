/* Rebinds the ov048 enemy's five animation tracks (x4: ov048/067/086/103): any animation object
 * still attached to a track is removed from the render object at +0x26c and its slot at +0x258
 * cleared, then every track is bound to the blend table at +0x354 with the given mode and
 * rewound to frame 0.
 *
 * Levers: `int mode` parameter (the s16 truncation for BindAnimTrack is hoisted into r8);
 * the slot is read as `((void **)(self + 0x258))[i]` but cleared through a differently spelt
 * address (`self + i * sizeof(void *) + 0x258`) -- the same spelling on both sides lets mwcc
 * keep the address in a callee-saved register across the remove call, the ROM recomputes it. */
typedef unsigned short u16;
typedef short s16;

extern void func_02014dc4(void *renderObj, void *anmObj);                    /* NNS_G3dRenderObjRemoveAnmObj */
extern void func_0202accc(void *animation, u16 track, void *table, s16 mode); /* BindAnimTrack */
extern void func_01fff774(void *animation, u16 track, int frame);             /* Anim_SetFrameWrapped */

void func_ov048_020b4050(char *self, int mode)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (((void **)(self + 0x258))[i] != 0) {
            func_02014dc4(self + 0x26c, (void *)((void **)(self + 0x258))[i]);
            *(void **)(self + i * sizeof(void *) + 0x258) = 0;
        }
        func_0202accc(self + 0x24c, (u16)i, *(void **)(self + 0x354), mode);
        func_01fff774(self + 0x24c, (u16)i, 0);
    }
}
