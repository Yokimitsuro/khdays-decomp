/* Reset the timer (+0x28=0), set the phase flags (+0x54=1, +0x4c=1) and run the pose
 * wrapper (anim 8 on both nodes) with handler 020ce750. */
extern void func_ov280_020d0cf4(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov280_020d23b4(int);
void func_ov280_020d237c(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x28) = 0;
    *(int *)(child + 0x54) = 1;
    *(signed char *)(child + 0x4c) = 1;
    func_ov280_020d0cf4(param_1, 8, 8, 0, (void *)&func_ov280_020d23b4);
}
