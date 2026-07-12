/* Unless the busy byte at *(child+4)+0xad is set, try to acquire the target (020d0ea4) into
 * (child)+0x10: if found, mark sub-state 4 and dispatch; otherwise play the anim (ov107 mode 1). */
extern int func_ov208_020d0ea4(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov107_020c9264(int a, int b, int c);
void func_ov208_020d1874(int param_1) {
    int child = *(int *)(param_1 + 4);
    int r;
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    r = func_ov208_020d0ea4(*(int *)child, 0);
    *(int *)(child + 0x10) = r;
    if (r != 0) {
        *(signed char *)(*(int *)child + 0x1c7) = 4;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    } else {
        func_ov107_020c9264(*(int *)child, 1, 0);
    }
}
