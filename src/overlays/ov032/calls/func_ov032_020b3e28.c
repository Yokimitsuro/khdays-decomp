/* Per-frame update of the ov032 enemy (and its byte-identical twins): reads the model's
 * track-0 frame, forwards the shared tick to the message handler (463c), and while the +0x2644
 * item's +0x30 sub-object is idle raises bit 16 of both 64-bit flag words (+0x464, +0x46c) on
 * the local player's session. Bit 2 of the +0x2c30 flags pins the frame at 0x1d000; the two
 * +0xdac animation blocks are wound to it on channels 0/1 while it is inside their length.
 * Finally 020ad588 runs. */
extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern int func_ov022_02083f90(void);
extern void func_ov032_020b463c(char *self, int tick);
extern int func_ov022_020912d8(char *sub);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern int func_0202aef8(void *animation, int track);
extern void func_01fff774(void *animation, int channel, int frame);
extern void func_ov022_020ad588(char *self);

struct b3 { unsigned char b0 : 1, b1 : 1, b2 : 1; };

void func_ov032_020b3e28(char *self)
{
    int frame;
    int i;
    char *anim;

    frame = func_0202aee0(*(char **)(self + 0x20) + 4, 0);
    func_ov032_020b463c(self, func_ov022_02083f90());
    if (func_ov022_020912d8(*(char **)(self + 0x2000 + 0x644) + 0x30) == 0) {
        if (func_02030788() == 0) {
            *(long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(long long *)(self + 0x46c) |= 0x10000;
        }
    }
    if (((struct b3 *)(self + 0x2000 + 0xc30))->b2 != 0) {
        frame = 0x1d000;
    }
    anim = self + 0x1ac + 0xc00;
    for (i = 0; i < 2; i++) {
        if (frame < func_0202aef8(anim, 0)) {
            func_01fff774(anim, 0, frame);
            func_01fff774(anim, 1, frame);
        }
        anim += 0x164;
    }
    func_ov022_020ad588(self);
}
