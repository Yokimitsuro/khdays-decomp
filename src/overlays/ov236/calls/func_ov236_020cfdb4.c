/* Clear +0x28 and the +0x51 byte, clear bit 0 of the +0x52 byte, set bit 0 of the u16 at
 * *(child)+0x1ae, play the anim (ov107 mode 0xa) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov236_020cfe10(int);
void func_ov236_020cfdb4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x28) = 0;
    *(signed char *)(child + 0x51) = 0;
    *(unsigned char *)(child + 0x52) &= ~1;
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    func_ov107_020c9264(*(int *)child, 0xa, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020cfe10);
}
