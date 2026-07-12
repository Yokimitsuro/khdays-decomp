/* Reset the sub-state (+0x1c6=0, +0x1c7=-1), clear bit0 of the hw60 hi byte and +0x1ae, then hand
 * off across the 020cf034 / 020cf158 / 020cf0ac trio. */
extern int func_0203c634(int, int, void *);
extern int func_ov283_020cf034(int);
extern int func_ov283_020cf158(int);
extern int func_ov283_020cf0ac(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov283_020cef98(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(unsigned char *)(*(int *)owner + 0x1c6) = 0;
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~1;
    *(unsigned short *)(*(int *)owner + 0x1ae) &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov283_020cf034);
    func_0203c634(param_1, 1, (void *)&func_ov283_020cf158);
    func_0203c634(param_1, 2, (void *)&func_ov283_020cf0ac);
}
