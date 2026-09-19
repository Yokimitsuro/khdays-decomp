/* Per-frame update of the mission enemy: samples the model's track-0 frame, forwards the
 * shared tick to the animation-argument pass (3aec), and while the +0x2644 record's +0x30
 * sub-object is idle raises bit 16 of both 64-bit flag words (+0x464, +0x46c) on the local
 * player's session. Then the 3828 pass and 020ad588 run. */
extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern int func_ov022_02083f90(void);
extern void func_ov062_020b62ec(char *self, int tick);
extern int func_ov022_020912d8(char *sub);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void func_ov062_020b6028(char *self);
extern void func_ov022_020ad588(char *self);

void func_ov062_020b5e28(char *self)
{
    func_0202aee0(*(char **)(self + 0x20) + 4, 0);
    func_ov062_020b62ec(self, func_ov022_02083f90());
    if (func_ov022_020912d8(*(char **)(self + 0x2000 + 0x644) + 0x30) == 0) {
        if (func_02030788() == 0) {
            *(long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(long long *)(self + 0x46c) |= 0x10000;
        }
    }
    func_ov062_020b6028(self);
    func_ov022_020ad588(self);
}
