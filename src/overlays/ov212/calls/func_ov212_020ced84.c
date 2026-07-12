/* Clear flags 0x82 in the high byte at (*child)+0x60; unless the busy byte at *(child+4)+0xad
 * is set, mark sub-state 2 and dispatch. */
extern int func_0203c634(int a, int b, void *handler);
struct node60_020ced84 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov212_020ced84(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct node60_020ced84 *)(*(int *)child + 0x60))->hi &= ~0x82;
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
