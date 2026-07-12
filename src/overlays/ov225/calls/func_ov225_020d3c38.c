/* Set anim (0x15 if child+0x78 else 0x16), clear +0x5c/+0x75/+0x76, then dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov225_020d3c88(void);
void func_ov225_020d3c38(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, *(int *)(child + 0x78) != 0 ? 0x15 : 0x16, 0);
    *(int *)(child + 0x5c) = 0;
    *(unsigned char *)(child + 0x75) = 0;
    *(unsigned char *)(child + 0x76) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov225_020d3c88);
}
