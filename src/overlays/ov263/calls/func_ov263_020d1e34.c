/* Set up the paired-pose sub-state (+0x4b=2, +0x28=0, +0x54=1) and run the pose wrapper
 * (anim 6 on both nodes) with handler 020ce210. */
extern void func_ov263_020d0cf4(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov263_020d1e70(int);
void func_ov263_020d1e34(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(signed char *)(child + 0x4b) = 2;
    *(int *)(child + 0x28) = 0;
    *(int *)(child + 0x54) = 1;
    func_ov263_020d0cf4(param_1, 6, 6, 0, (void *)&func_ov263_020d1e70);
}
