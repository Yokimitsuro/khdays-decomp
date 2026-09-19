/* Set bit 0x40 in the high byte of the u16 flags at *(child)+0x60, clear +0x40, run the local
 * 020cf... pass on the child, play the anim (ov107 mode 0xa,0), fire ov107_020c5af8(*child,
 * 0x15e, 0xc, *(child+8)), then register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern void func_ov266_020cf3dc(int child, int a, int b);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov266_020d19b0(int);
void func_ov266_020d192c(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)child + 0x60))->hi |= (unsigned char)0x40;
    *(int *)(child + 0x40) = 0;
    func_ov266_020cf3dc(child, 1, 0);
    func_ov107_020c9264(*(int *)child, 0xa, 0);
    func_ov107_020c5af8(*(int *)child, 0x15e, 0xc, *(int *)(child + 8));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d19b0);
}
