/* Run the local setup (020cc9e0), set up the paired-pose sub-state (+0x28=0, +0x54=1,
 * +0x4c=1) and run the pose wrapper (anim 7 on both nodes) with handler 020ce4b0. */
extern void func_ov263_020d0628(int);
extern void func_ov263_020d0cf4(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov263_020d2110(int);
void func_ov263_020d20cc(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov263_020d0628(param_1);
    *(int *)(child + 0x28) = 0;
    *(int *)(child + 0x54) = 1;
    *(signed char *)(child + 0x4c) = 1;
    func_ov263_020d0cf4(param_1, 7, 7, 0, (void *)&func_ov263_020d2110);
}
