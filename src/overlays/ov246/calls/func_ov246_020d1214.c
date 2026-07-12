/* Set anim 5; if the target object (+0x48) exists, aim toward it via VEC_Subtract
 * + func_020050b4 and store the angle at +0x10/+0xc; then dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern int func_020050b4(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov246_020d1284(void);
void func_ov246_020d1214(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 5, 0);
    {
        int target = *(int *)(child + 0x48);
        if (target != 0) {
            int diff[3];
            VEC_Subtract((const void *)(target + 0x190), (const void *)(*(int *)child + 0xb0), diff);
            int r = func_020050b4(diff[0], diff[2]);
            *(int *)(child + 0x10) = r;
            *(int *)(child + 0xc) = r;
        }
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov246_020d1284);
}
