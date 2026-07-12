/* Clear bit 1 of the render flags at *(child+4)+0x5c, (re)configure the four spline
 * channels (indices 0,1,2,4 at rate 0), then register the handler. */
extern void func_0203b9fc(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov275_020d2748(int);
void func_ov275_020d269c(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(*(int *)(child + 4) + 0x5c) &= ~2;
    func_0203b9fc(*(int *)(child + 4), 0, 0, 0);
    func_0203b9fc(*(int *)(child + 4), 1, 0, 0);
    func_0203b9fc(*(int *)(child + 4), 2, 0, 0);
    func_0203b9fc(*(int *)(child + 4), 4, 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov275_020d2748);
}
