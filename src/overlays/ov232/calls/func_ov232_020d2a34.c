/* Compute the offset vector (020cca74) into (child)+0x30; unless the gate byte at
 * *(child+0x10) is set, advance the step counter (+0x28): on the 3rd step mark sub-state
 * 2 and dispatch, otherwise re-pose both nodes (ov107 mode counter+0xd). */
extern void func_ov232_020d06b4(void *out, int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
struct Vec3_020cedf4 { int x, y, z; };
void func_ov232_020d2a34(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct Vec3_020cedf4 out;
    int counter;
    func_ov232_020d06b4(&out, param_1, *(int *)(*(int *)child + 0x388) + 0x2c);
    *(struct Vec3_020cedf4 *)(child + 0x30) = out;
    if (*(unsigned char *)*(int *)(child + 0x10) != 0) return;
    counter = *(int *)(child + 0x28) + 1;
    *(int *)(child + 0x28) = counter;
    if (counter == 3) {
        *(signed char *)(*(int *)child + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    } else {
        func_ov107_020c9264(*(int *)child, counter + 0xd, 0);
        func_ov107_020c9ee8(*(int *)(*(int *)child + 0x388), *(int *)(child + 0x28) + 0xd, 0);
    }
}
