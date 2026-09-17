/* Per-frame update of the ov049 enemy (x4: ov049/068/087/104): reads the node's animation frame,
 * feeds the attachment with the current tick and steps it; when the attachment reports idle, the
 * two 64-bit flag words at +0x464 and +0x46c get bit 16 (each guarded by 02030788 being idle);
 * then the two secondary channels at +0xda8 (0x164 apart) are driven from their configs at
 * +0x2c54 (0x54 apart) with the heading at +0x2aba and the frame, and the common post-update
 * runs. */
extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(void *attach, int tick);
extern void func_ov022_02091474(void *attach);
extern int func_ov022_020912d8(void *attach);
extern int func_02030788(void);
extern void func_ov002_020521e4(char *channel, char *config, int heading, int frame);
extern void func_ov022_020ad588(char *self);

void func_ov104_020bae24(char *self)
{
    int frame = func_0202aee0(*(char **)(self + 0x20) + 4, 0);
    int i;
    char *config;
    char *channel;

    func_ov022_0209145c(*(void **)(self + 0x2644), func_ov022_02083f90());
    func_ov022_02091474(*(void **)(self + 0x2644));
    if (func_ov022_020912d8(*(void **)(self + 0x2644)) == 0) {
        if (func_02030788() == 0) {
            *(long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(long long *)(self + 0x46c) |= 0x10000;
        }
    }
    config = self + 0x54 + 0x2c00;
    channel = self + 0x1a8 + 0xc00;
    for (i = 0; i < 2; i++) {
        func_ov002_020521e4(channel, config, *(short *)(self + 0x2aba), frame);
        config += 0x54;
        channel += 0x164;
    }
    func_ov022_020ad588(self);
}
