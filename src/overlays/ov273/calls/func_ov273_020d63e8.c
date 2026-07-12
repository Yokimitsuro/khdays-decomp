/* Clear the +0x1c6 byte, mark sub-state -1, set +4 = *(child)+0xb0 and register two handlers
 * in turn (slot 1 then slot 0). */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d64dc(int);
extern void func_ov273_020d6440(int);
void func_ov273_020d63e8(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(signed char *)(*(int *)child + 0x1c6) = 0;
    *(signed char *)(*(int *)child + 0x1c7) = -1;
    *(int *)(child + 4) = *(int *)child + 0xb0;
    func_0203c634(param_1, 1, (void *)&func_ov273_020d64dc);
    func_0203c634(param_1, 0, (void *)&func_ov273_020d6440);
}
