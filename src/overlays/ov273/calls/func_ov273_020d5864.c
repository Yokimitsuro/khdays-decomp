/* Clear the +0x1c6 byte, mark sub-state -1, set +4 = *(child)+0xb0 and register three handlers
 * in turn (slots 1, 0, 2). */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d59cc(int);
extern void func_ov273_020d58d4(int);
extern void func_ov273_020d599c(int);
void func_ov273_020d5864(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(signed char *)(*(int *)child + 0x1c6) = 0;
    *(signed char *)(*(int *)child + 0x1c7) = -1;
    *(int *)(child + 4) = *(int *)child + 0xb0;
    func_0203c634(param_1, 1, (void *)&func_ov273_020d59cc);
    func_0203c634(param_1, 0, (void *)&func_ov273_020d58d4);
    func_0203c634(param_1, 2, (void *)&func_ov273_020d599c);
}
