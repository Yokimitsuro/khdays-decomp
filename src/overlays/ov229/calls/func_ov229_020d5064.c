/* Resolve the target via func_ov107_020cab14 into +0x3bc; if none, mark state 2
 * and dispatch (null handler); else set anim 0x16, clear +0x4c/+0x62/+0x61, and
 * dispatch. */
extern int func_ov107_020cab14(int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov229_020d50e0(void);
void func_ov229_020d5064(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(*(int *)child + 0x3bc) = func_ov107_020cab14(*(int *)child, 0);
    if (*(int *)(*(int *)child + 0x3bc) == 0) {
        *(signed char *)(*(int *)child + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
        return;
    }
    func_ov107_020c9264(*(int *)child, 0x16, 0);
    *(int *)(child + 0x4c) = 0;
    *(unsigned char *)(child + 0x62) = 0;
    *(unsigned char *)(child + 0x61) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov229_020d50e0);
}
