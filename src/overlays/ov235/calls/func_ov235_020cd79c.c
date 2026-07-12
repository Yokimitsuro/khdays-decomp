/* Unless the busy byte at *(child+0xc) is set, clear bit 0x40 in the high byte of the u16 flags
 * at *(obj)+0x60, clear the +0x65 byte, play the anim (ov107 mode 0x1e) and register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov235_020cd810(int);
void func_ov235_020cd79c(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x40;
    *(signed char *)(child + 0x65) = 0;
    func_ov107_020c9264(*(int *)child, 0x1e, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov235_020cd810);
}
