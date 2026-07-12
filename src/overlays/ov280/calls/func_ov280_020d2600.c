/* Reset the timer (+0x28=0), set the phase flag (+0x54=1) and run the pose wrapper
 * (anim 9 on both nodes) with handler 020ce9d0. */
extern void func_ov280_020d0cf4(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov280_020d2634(int);
void func_ov280_020d2600(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x28) = 0;
    *(int *)(child + 0x54) = 1;
    func_ov280_020d0cf4(param_1, 9, 9, 0, (void *)&func_ov280_020d2634);
}
