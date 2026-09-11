typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(int *a, int *b, int *out);
extern int func_01ff8d18(const Vec3 *source, Vec3 *destination);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c0b90(int owner, int a, Vec3 v, int flag);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov283_020ce2a0(int);

void func_ov283_020ce214(int *self) {
    int state = self[1];
    int q = *(int *)state;
    Vec3 *a = (Vec3 *)(*(int *)(q + 0x390) + 0x190);
    Vec3 *b = (Vec3 *)(q + 0x74);
    Vec3 diff;
    VEC_Subtract((int *)a, (int *)b, (int *)&diff);

    func_01ff8d18(&diff, &diff);

    int angle = func_020050b4(diff.x, diff.z);
    *(int *)(state + 0x40) = angle;
    *(int *)(state + 0x38) = angle;

    Vec3 v = *(Vec3 *)(*(int *)(state + 8));
    q = *(int *)state;
    func_ov107_020c0b90(q, 1, v, 0);

    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (void *)&func_ov283_020ce2a0);
}
