/* func_ov000_0204ede0 -- request the logo->title transition, ov000. Fades the screen
 * (func_020335ec/func_02033c24), then latches scene 7 with an arg reflecting whether
 * the logo already finished (heap+0x4c30==0). Returns the spawn sentinel (-2). */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_020335ec(int);
extern void func_02033c24(int, int);
extern void func_02020a78(int scene, int arg);
int func_ov000_0204ede0(void) {
    char *h = (char *)NNSi_FndGetCurrentRootHeap();
    int arg = (*(signed char *)(h + 0x4c30) == 0);
    func_020335ec(0x1f);
    func_02033c24(0x40, 0xa);
    func_02020a78(7, arg);
    return -2;
}
