/* Clear flags 1,2 in the high byte of the u16 at (*child)+0x60, set bit0 of the
 * u16 at +0x1ae, then dispatch. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov278_020cfb30(void);
struct hi_020cfb2c { unsigned short pad : 8; unsigned short flags : 8; };
void func_ov278_020cfad4(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct hi_020cfb2c *)(*(int *)child + 0x60))->flags &= ~6;
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020cfb30);
}
