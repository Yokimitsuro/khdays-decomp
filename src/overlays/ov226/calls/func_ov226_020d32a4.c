/* Unless the grandchild is busy (+0xad), set anim 0x13, run func_ov226_020d0fc0,
 * then dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov226_020d0fc0(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov226_020d32f4(void);
void func_ov226_020d32a4(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)child, 0x13, 0);
    func_ov226_020d0fc0(*(int *)child, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov226_020d32f4);
}
