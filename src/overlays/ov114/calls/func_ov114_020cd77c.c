/* Set bit 0 of the u16 at *(child)+0x1ae, clear bit 0 of the low byte at *(*child+0x388)+8,
 * play the anim (ov107 mode 7), clear +0x44, set *(*child)+0x390 = 0xcc and register the handler. */
struct b8 { unsigned int f : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov114_020cd800(int);
void func_ov114_020cd77c(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*(int *)child + 0x388) + 8))->f &= ~1;
    func_ov107_020c9264(*(int *)child, 7, 0);
    *(int *)(child + 0x44) = 0;
    *(int *)(*(int *)child + 0x390) = 0xcc;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov114_020cd800);
}
