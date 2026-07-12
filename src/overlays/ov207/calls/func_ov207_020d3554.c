/* Per-frame spline advance: set the target rate (+0x3c = owner_rate*30/20), compute the
 * heading angle (+0x44), step the parameter (+0x34) down by the fixed-point owner rate,
 * mirror the pose vector (+0x30 -> +0x14), and when the parameter underflows mark sub-state 0xb. */
extern int func_020050b4(int a, int b);
struct Vec3_020cf914 { int x, y, z; };
void func_ov207_020d3554(int param_1) {
    int child = *(int *)(param_1 + 4);
    int m;
    *(int *)(child + 0x3c) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 20;
    *(int *)(child + 0x44) = func_020050b4(*(int *)(child + 0x30), *(int *)(child + 0x38));
    m = *(int *)(*(int *)param_1 + 0x2c) * 30;
    *(int *)(child + 0x34) -= (int)((((long long)m << 8) + 0x800) >> 12);
    *(struct Vec3_020cf914 *)(child + 0x14) = *(struct Vec3_020cf914 *)(child + 0x30);
    if (*(int *)(child + 0x34) < 0) {
        *(signed char *)(*(int *)child + 0x1c7) = 0xb;
    }
}
