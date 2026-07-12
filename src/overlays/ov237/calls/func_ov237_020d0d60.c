/* Point +8 at the linked node's +0x42c socket +0x14, reset the sub-state (+0x1c6=0, +0x1c7=-1),
 * clear bit0 of the hw60 hi byte and +0x1ae, then hand off across the 020d0e10/020d0ea0/020d0e88 trio. */
extern int func_0203c634(int, int, void *);
extern int func_ov237_020d0e10(int);
extern int func_ov237_020d0ea0(int);
extern int func_ov237_020d0e88(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov237_020d0d60(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 8) = *(int *)(*(int *)(*(int *)owner + 0x390) + 0x42c) + 0x14;
    *(unsigned char *)(*(int *)owner + 0x1c6) = 0;
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~1;
    *(unsigned short *)(*(int *)owner + 0x1ae) &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov237_020d0e10);
    func_0203c634(param_1, 1, (void *)&func_ov237_020d0ea0);
    func_0203c634(param_1, 2, (void *)&func_ov237_020d0e88);
}
