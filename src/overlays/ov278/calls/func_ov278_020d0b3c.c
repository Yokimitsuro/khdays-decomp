/* Unless busy, kick anim (0xe, phase 1), clear +0x28, seed the pose and clear +0x4c, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern void MI_CpuFill8(void *dst, int val, int size);
extern int func_0203c634(int, int, void *);
extern int data_02041dc8;
extern int func_ov278_020d0bac(int);
struct w3 { int a, b, c; };
void func_ov278_020d0b3c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0xe, 1);
    *(int *)(owner + 0x28) = 0;
    *(struct w3 *)(owner + 0x3c) = *(struct w3 *)&data_02041dc8;
    MI_CpuFill8((void *)(owner + 0x4c), 0, 4);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d0bac);
}
