/* Clear flag 0 in the high byte at (*child)+0x60, clear bit 0 in the low byte of [+8] of the
 * child slot at (*child)+0x388, then register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov212_020d1ef0(int);
struct node60_020d1e80 { unsigned short lo : 8; unsigned short hi : 8; };
struct lo8_020d1e80 { unsigned f : 8; };
void func_ov212_020d1e80(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct node60_020d1e80 *)(*(int *)child + 0x60))->hi &= ~1;
    {
        int c = *(int *)(*(int *)child + 0x388);
        ((struct lo8_020d1e80 *)(c + 8))->f &= ~1;
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020d1ef0);
}
