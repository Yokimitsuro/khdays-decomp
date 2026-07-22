/* Re-aim the actor: when the caller asks for it, take the delta between the
 * points at +0x14 and +0x20 and turn the orientation at +0x2c toward it, then
 * commit either way. The turn is skipped in the boot mode where data_0204be04
 * is set. */
typedef struct {
    int x, y, z;
} VecFx32;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_02033ef8(void *from, const VecFx32 *delta, void *out);
extern void func_02023cc0(void *actor);

extern unsigned char data_0204be04;

void func_ov002_0204cac0(char *self, int reaim) {
    char *actor = *(char **)(self + 0x20);
    VecFx32 delta;

    if (reaim != 0) {
        VEC_Subtract((VecFx32 *)(actor + 0x14), (VecFx32 *)(actor + 0x20), &delta);

        if (data_0204be04 == 0) {
            func_02033ef8(actor + 0x20, &delta, actor + 0x2c);
        }
    }

    func_02023cc0(actor);
}
