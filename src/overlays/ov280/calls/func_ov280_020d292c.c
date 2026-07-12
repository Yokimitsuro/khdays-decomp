/* Compute the offset vector (020cca74) into (child)+0x30; unless the gate byte at
 * *(child+0x10) is set, advance the step counter (+0x28): steps 0-1 pose both nodes with
 * anim 1, step 2 with anim 0xc, and from step 3 mark sub-state 2 and dispatch. */
extern void func_ov280_020d06bc(void *out, int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
struct Vec3_020cecc8 { int x, y, z; };
void func_ov280_020d292c(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct Vec3_020cecc8 out;
    int counter;
    func_ov280_020d06bc(&out, param_1, *(int *)(*(int *)child + 0x388) + 0x2c);
    *(struct Vec3_020cecc8 *)(child + 0x30) = out;
    if (*(unsigned char *)*(int *)(child + 0x10) != 0) return;
    counter = *(int *)(child + 0x28) + 1;
    *(int *)(child + 0x28) = counter;
    if (counter < 2) {
        func_ov107_020c9264(*(int *)child, 1, 0);
        func_ov107_020c9ee8(*(int *)(*(int *)child + 0x388), 1, 0);
    } else if (counter < 3) {
        func_ov107_020c9264(*(int *)child, 0xc, 0);
        func_ov107_020c9ee8(*(int *)(*(int *)child + 0x388), 0xc, 0);
    } else {
        *(signed char *)(*(int *)child + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    }
}
