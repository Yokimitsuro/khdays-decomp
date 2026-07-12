/* Skip if the grandchild busy flag (+0xad) is set; else set anim 0x12 and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov225_020d3608(void);
void func_ov225_020d35c4(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)child, 0x12, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov225_020d3608);
}
