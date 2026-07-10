extern void VEC_Add(int *a, int *b, int *c);
extern void func_01ffa724(int scale, int *src, int *dst);
extern int VEC_Mag(int *v);

struct Vec3_02097f08 { int x, y, z; };

void func_ov022_02097f08(int obj) {
    struct Vec3_02097f08 stack;
    int m;
    *(unsigned long long *)obj &= ~0x80000000000LL;
    if (*(int *)(obj + 0x4a4) == 0 && *(int *)(obj + 0x4ac) == 0) return;
    stack = *(struct Vec3_02097f08 *)(obj + 0x4a4);
    stack.y = 0;
    VEC_Add((int *)(obj + 0x498), (int *)&stack, (int *)(obj + 0x498));
    func_01ffa724(0x800, (int *)(obj + 0x4a4), (int *)(obj + 0x4a4));
    m = VEC_Mag((int *)(obj + 0x4a4));
    if (m > 0x19a) {
        *(unsigned long long *)obj |= 0x80000000000LL;
        return;
    }
    if (m < 0x29) {
        *(int *)(obj + 0x4ac) = 0;
        *(int *)(obj + 0x4a8) = 0;
        *(int *)(obj + 0x4a4) = 0;
    }
}
