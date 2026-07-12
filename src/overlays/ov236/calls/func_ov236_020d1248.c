/* Unless the busy byte at *(child+4)+0xad is set, clear bit 0 of the u16 at *(child)+0x1ae,
 * play the anim (ov107 mode 0x11,1), clear +0x28, set the +0x51 byte to 1 and register the
 * handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov236_020d12b0(int);
void func_ov236_020d1248(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    *(unsigned short *)(*(int *)child + 0x1ae) &= ~1;
    func_ov107_020c9264(*(int *)child, 0x11, 1);
    *(int *)(child + 0x28) = 0;
    *(signed char *)(child + 0x51) = 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d12b0);
}
