typedef struct { int x, y, z; } Vec3;
struct T { int a, b, c, d; };
struct S { struct T t; char pad[0x28 - 16]; unsigned char flag; };

extern int func_0203d040(int cur, int target, int step, int flag);
extern void func_0202f188(int *out, int *axis, int angle);
extern void func_0202ed60(void *dst, void *axis, int src);
extern void func_0202ef54(void *a, void *b, void *c);
extern int func_0203c9d0(struct S *dst, struct S *src);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *source, Vec3 *destination);
extern void func_01ffa724(int factor, int *src, int *dst);
extern void INITi_CpuClear32_0x01ff86fc(int value, void *dst, int size);
extern int data_02042264[3];

void func_ov210_020d0a48(int *self) {
    int *state = (int *)self[1];
    int quat[4];
    struct T tmp;
    int newAngle;
    Vec3 *v;

    newAngle = func_0203d040(state[9], state[0xa],
        (int)((((long long)*(int *)(self[0] + 0x2c) * state[0x14]) + 0x800) >> 12), 0);
    func_0202f188(quat, data_02042264, state[9] = newAngle);
    func_0202ed60(&tmp, data_02042264, *state + 0x124);
    func_0202ef54(&tmp, &tmp, quat);
    func_0203c9d0((struct S *)(*state + 0xa0), (struct S *)&tmp);
    if (VEC_Mag((Vec3 *)(state + 5)) > 0x2000) {
        func_01ff8d18((Vec3 *)(state + 5), (Vec3 *)(state + 5));
        func_01ffa724(0x2000, (int *)(state + 5), (int *)(state + 5));
    }
    v = (Vec3 *)(state + 5);
    *(Vec3 *)(*state + 0xf0) = *v;
    INITi_CpuClear32_0x01ff86fc(0, v, 0xc);
    if (state[0x1b] > 0) {
        state[0x1b] -= *(int *)(self[0] + 0x2c);
    }
}
