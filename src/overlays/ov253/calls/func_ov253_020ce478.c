/* For each of the three rigs: copy the anchor position from +0x390's block into +0x58 of
 * the rig at +0x3a0, take the vector from there to +0x394's block and store its squared
 * length at +0x18.
 *
 * Three levers: the three tables are ARRAY INDICES with their offsets folded in
 * (0x3a0/4 = 0xe8, 0x390/4 = 0xe4, 0x394/4 = 0xe5) so the ROM's single `add r3,r5,r4,lsl#2`
 * survives; the counter is bumped AFTER the second call (mwcc hoists it above the bl
 * otherwise); and `i` must be declared last so it lands in r4 and the context in r5. */
typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *a, Vec3 *b);

void func_ov253_020ce478(int unused, char **arg) {
    char **ctx;
    char *e;
    int i;
    i = 0;
    ctx = arg;
    do {
        e = ctx[i + 0xe8] + 0x58;
        *(Vec3 *)e = *(Vec3 *)(ctx[i + 0xe4] + 0x14);
        VEC_Subtract((Vec3 *)(ctx[i + 0xe5] + 0x14), (Vec3 *)e, (Vec3 *)(e + 0xc));
        *(int *)(e + 0x18) = func_01ff8d18((Vec3 *)(e + 0xc), (Vec3 *)(e + 0xc));
        i = i + 1;
    } while (i < 3);
}
