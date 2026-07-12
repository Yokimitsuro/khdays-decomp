/* Unless the busy byte at *(child+4)+0xad is set, fire ov107_020c5af8(*child, 0x15e, 0xb,
 * *(child+8)), run ov266_020d0168, play the anim (ov107 mode 7,1) and register the handler. */
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_ov267_020d1f88(int a);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov267_020d3254(int);
void func_ov267_020d31f0(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c5af8(*(int *)child, 0x15e, 0xb, *(int *)(child + 8));
    func_ov267_020d1f88(child);
    func_ov107_020c9264(*(int *)child, 7, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d3254);
}
