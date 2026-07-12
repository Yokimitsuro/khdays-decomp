/* Stop the anim (ov107 mode 0,0), clear flags 0x8e in the high byte at (*child)+0x60, set
 * bit 0 of the halfword at (*child)+0x1ae, seed the timer (+0x50=0xa000) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov282_020d0ca0(int);
struct node60_020d0c18 { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov282_020d0c24(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0, 0);
    ((struct node60_020d0c18 *)(*(int *)child + 0x60))->hi &= ~0x8e;
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    *(int *)(child + 0x50) = 0xa000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov282_020d0ca0);
}
