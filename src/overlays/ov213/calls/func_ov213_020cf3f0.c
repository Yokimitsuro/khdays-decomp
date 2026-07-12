/* Play the anim (ov107 mode 0xe), clear bit 0x40 in the high byte of the u16 flags at
 * *(child)+0x60 and register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020cf450(int);
void func_ov213_020cf3f0(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xe, 0);
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x40;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov213_020cf450);
}
