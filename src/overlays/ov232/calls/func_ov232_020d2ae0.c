/* Set the flip flag (+0x4a=1) and run the pose wrapper (anim 2 on both nodes) with handler 020cdc90. */
extern void func_ov232_020d0cd4(int p1, int p2, int p3, int p4, void *handler);
extern void func_ov232_020d18d0(int);
void func_ov232_020d2ae0(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(signed char *)(child + 0x4a) = 1;
    func_ov232_020d0cd4(param_1, 2, 2, 0, (void *)&func_ov232_020d18d0);
}
