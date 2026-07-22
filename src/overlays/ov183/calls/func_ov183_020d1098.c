/* Acquire the target and set up the charge: with no target, latch entry-anim 2
 * and dispatch null. Otherwise take the distance the query wrote to the stack,
 * subtract both bodies' radii to get the gap, work out the approach speed from
 * the scene rate (x30/5), aim at the target, build the orientation matrix and
 * scale it, and -- unless the abort byte is up -- start animation 3 and hand
 * over to the charge handler. */
struct Vec3 { int x, y, z; };
extern int func_ov107_020cab14(int owner, int *out);
extern void func_0203c634(void *self, int index, void *handler);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(void *a, void *b, struct Vec3 *out);
extern int func_020050b4(int dx, int dz);
extern void func_0202f384(void *dst, void *src, const void *table);
extern void func_01ffa724(int scale, void *dst, void *src);
extern void func_ov107_020c9264(int model, int anim, int mode);
extern const int data_02042258[];
extern void func_ov183_020d11b8(void);

void func_ov183_020d1098(int *self) {
    int *obj = (int *)self[1];
    int gap;
    struct Vec3 delta;
    int me;
    int target;

    target = obj[4] = func_ov107_020cab14(obj[0], &gap);

    if (target == 0) {
        *(unsigned char *)(obj[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }

    {
        me = obj[0];

        gap = FX_Sqrt(gap) - (*(int *)(target + 0x80) + *(int *)(me + 0x80));
    }

    obj[8] = *(int *)(self[0] + 0x2c) * 30 / 10;

    VEC_Subtract((void *)(obj[4] + 0x74), (void *)obj[2], &delta);
    obj[6] = func_020050b4(delta.x, delta.z);

    func_0202f384((char *)obj + 0x54, (void *)(obj[0] + 0xa0), data_02042258);
    func_01ffa724(0x100, (char *)obj + 0x54, (char *)obj + 0x54);

    if (*(unsigned char *)obj[3] != 0) {
        return;
    }

    func_ov107_020c9264(obj[0], 4, 0);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov183_020d11b8);
}
