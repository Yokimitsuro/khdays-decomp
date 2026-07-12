/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x20; while below 0x2a8 keep
 * running the sub-update (020d238c). Then, unless the gate byte at *(*child+0x384)+0xad is
 * set, reset the sub-state byte (+0x1c7) and dispatch. */
extern void func_ov229_020d5fcc(int);
extern int func_0203c634(int a, int b, void *handler);
void func_ov229_020d6814(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x20) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x20) = t;
    if (t <= 0x2a8) func_ov229_020d5fcc(child);
    if (*(unsigned char *)(*(int *)(*(int *)child + 0x384) + 0xad) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
