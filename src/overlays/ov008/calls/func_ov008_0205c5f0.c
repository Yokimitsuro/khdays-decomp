/* Reposition the info window: mirror the masked X (param_1 & 0x1ff) into engine A BG1 H/V scroll,
 * scroll the render context by -param_1*0x1000, and set the window bounds (WIN0H from 0x68/0xe9
 * minus param_1) and control (param_2 low byte | 0x1800). */
extern int func_ov008_02050c54(void);
extern void func_ov008_020549dc(int ctx, int dx, int flag);
extern void func_ov008_020543a0(int ctx, int flag);

void func_ov008_0205c5f0(unsigned int param_1, unsigned short param_2) {
    volatile unsigned int *pScroll = (volatile unsigned int *)0x04000014;
    volatile unsigned short *pWin = (volatile unsigned short *)0x04000040;
    unsigned int v = param_1 & 0x1ff;
    int ctx;
    pScroll[0] = v;
    pScroll[1] = v;
    ctx = func_ov008_02050c54();
    func_ov008_020549dc(ctx, param_1 * -0x1000, 0);
    func_ov008_020543a0(ctx, 0);
    pWin[0] = ((0x68 - param_1) << 8 & 0xff00) | ((0xe9 - param_1) & 0xff);
    pWin[2] = (param_2 & 0xff) | 0x1800;
}
