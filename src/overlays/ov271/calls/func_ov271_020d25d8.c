/* Raise bit 1 of the render flags (+0x5c) on the four sub-objects at (child)+4/+8/+0xc/+0x10,
 * then dispatch (no handler). */
extern int func_0203c634(int a, int b, void *handler);
void func_ov271_020d25d8(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(*(int *)(child + 4) + 0x5c) |= 2;
    *(int *)(*(int *)(child + 8) + 0x5c) |= 2;
    *(int *)(*(int *)(child + 0xc) + 0x5c) |= 2;
    *(int *)(*(int *)(child + 0x10) + 0x5c) |= 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
