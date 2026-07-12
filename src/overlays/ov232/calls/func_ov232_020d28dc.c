/* Reset the timer (+0x28=0) and run the pose wrapper (anim 0xc on both nodes) with handler 020cecc8. */
extern void func_ov232_020d0cd4(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov232_020d2908(int);
void func_ov232_020d28dc(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x28) = 0;
    func_ov232_020d0cd4(param_1, 0xc, 0xc, 0, (void *)&func_ov232_020d2908);
}
