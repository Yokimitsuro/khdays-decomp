/* Reset the timer (+0x28=0) and run the pose wrapper (anim 0xc on both nodes) with handler 020cecc8. */
extern void func_ov265_020d0ce8(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov265_020d2920(int);
void func_ov265_020d28f4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x28) = 0;
    func_ov265_020d0ce8(param_1, 0xc, 0xc, 0, (void *)&func_ov265_020d2920);
}
