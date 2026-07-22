/* Copies the owner's position into the sub-object at +0x58, takes the vector to the target
 * at +0x14 of the block at +0x3b8, stores its squared length at +0x70 (never 0), and closes
 * the update. */
typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *a, Vec3 *b);
extern void func_ov107_020c7ca4(char *self);

void func_ov245_020d20c0(char *self) {
    char *o = *(char **)(self + 0x388);
    Vec3 *v = (Vec3 *)(o + 0x58);
    *v = *(Vec3 *)(self + 0xb0);
    VEC_Subtract((Vec3 *)(*(char **)(self + 0x3b8) + 0x14), v, (Vec3 *)(o + 0x64));
    *(int *)(o + 0x70) = func_01ff8d18((Vec3 *)(o + 0x64), (Vec3 *)(o + 0x64));
    if (*(int *)(o + 0x70) == 0) {
        *(int *)(o + 0x70) = 1;
    }
    func_ov107_020c7ca4(self);
}
