/* Per-frame update of the ov039 enemy (x4: ov039/058/078/095): reads the node's animation frame
 * and drives the first secondary channel (+0xda8 from the config at +0x2c2c); by mode: 0x2f and
 * 0x32 refresh both attack anchors on the emitter's context (slot 5) while it is idle, 0x33
 * clears them, 0x17-0x19 and 0x1e-0x2d raise bit 0 of the +0xf0c channel flags when the local
 * flag bit 12 / bit 4 is set and the +0xf0d byte is non-zero; then the second channel (+0xf0c
 * from +0x2c80) is driven, the attachment stepped, an idle attachment flags the local player's
 * bit 16 in both words, and the common post-update runs. */
typedef struct { int x, y, z; } Vec3;

extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern void func_ov002_020521e4(char *channel, char *config, int heading, int frame);
extern int func_ov022_020923dc(char *emitter, int slot);
extern void func_ov058_020b6850(char *self, int side, Vec3 *out);
extern void func_ov022_02089478(int context, int slot, Vec3 *at);
extern void func_ov022_02089524(int context, int slot);
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(void *attach, int tick);
extern void func_ov022_02091474(void *attach);
extern int func_ov022_020912d8(void *attach);
extern int func_02030788(void);
extern void func_ov022_020ad588(char *self);

void func_ov058_020b6088(char *self)
{
    Vec3 at;
    int frame = func_0202aee0(*(char **)(self + 0x20) + 4, 0);
    int i;
    int context;

    func_ov002_020521e4(self + 0x1a8 + 0xc00, self + 0x2c + 0x2c00, *(short *)(self + 0x2aba), frame);
    switch (*(int *)(self + 0x6bc)) {
    case 0x17:
    case 0x18:
    case 0x19:
        if ((*(unsigned long long *)(self + 0x464) & 0x1000) != 0 && *(signed char *)(self + 0xf0d) != 0) {
            *(unsigned char *)(self + 0xf0c) |= 1;
        }
        break;
    case 0x2f:
    case 0x32:
        if (func_ov022_020923dc(self + 0x248 + 0x2400, 5) == 0) {
            context = *(int *)(self + 0x2000 + 0x65c);
            for (i = 0; i < 2; i++) {
                func_ov058_020b6850(self, i, &at);
                func_ov022_02089478(context, i, &at);
            }
        }
        break;
    case 0x33:
        if (func_ov022_020923dc(self + 0x248 + 0x2400, 5) == 0) {
            context = *(int *)(self + 0x2000 + 0x65c);
            for (i = 0; i < 2; i++) {
                func_ov022_02089524(context, i);
            }
        }
        break;
    default:
        if (*(int *)(self + 0x6bc) >= 0x1e && *(int *)(self + 0x6bc) < 0x2e) {
            if ((*(unsigned long long *)(self + 0x464) & 0x10) != 0 && *(signed char *)(self + 0xf0d) != 0) {
                *(unsigned char *)(self + 0xf0c) |= 1;
            }
        }
        break;
    }
    func_ov002_020521e4(self + 0x30c + 0xc00, self + 0x2c80, *(short *)(self + 0x2aba), frame);
    func_ov022_0209145c(*(void **)(self + 0x2644), func_ov022_02083f90());
    func_ov022_02091474(*(void **)(self + 0x2644));
    if (func_ov022_020912d8(*(void **)(self + 0x2644)) == 0) {
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x46c) |= 0x10000;
        }
    }
    func_ov022_020ad588(self);
}
