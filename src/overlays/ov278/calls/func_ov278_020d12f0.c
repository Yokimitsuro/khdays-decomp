/* Unless the busy byte at *(child+4)+0xad is set, choose sub-state 9 or 0xa for the two
 * sub-objects at *(obj)+0x3b4 / +0x3b8: pick 9 if either sub-object is idle (bit 0 of its
 * +0x3c0/+0x3d4 flag clear AND bit 1 of the u16 at +0x1ac clear), otherwise 0xa. Dispatch NULL. */
struct sbit0 { int b : 1; };
extern int func_0203c634(int a, int b, void *handler);
void func_ov278_020d12f0(int param_1) {
    int child = *(int *)(param_1 + 4);
    int obj = *(int *)child;
    int a = *(int *)(obj + 0x3b4);
    int b = *(int *)(obj + 0x3b8);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    if ((!((struct sbit0 *)(a + 0x3c0))->b && (*(unsigned short *)(a + 0x1ac) & 2) == 0) ||
        (!((struct sbit0 *)(b + 0x3d4))->b && (*(unsigned short *)(b + 0x1ac) & 2) == 0)) {
        *(signed char *)(obj + 0x1c7) = 9;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    } else {
        *(signed char *)(obj + 0x1c7) = 0xa;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
    }
}
