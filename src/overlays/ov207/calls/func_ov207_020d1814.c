/* Unless the gate byte at *(child+0xc) is set, pose the sub-node at (*child)+0x3b4 (ov107
 * mode 0,1) and the main node (ov107 mode 2,1), then register the handler. */
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov207_020d186c(int);
void func_ov207_020d1814(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    func_ov107_020c9ee8(*(int *)(*(int *)child + 0x3b4), 0, 1);
    func_ov107_020c9264(*(int *)child, 2, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov207_020d186c);
}
