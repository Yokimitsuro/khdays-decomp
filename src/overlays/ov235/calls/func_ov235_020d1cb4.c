/* Accumulate the owner rate (+0x2c) into the timer at (child)+8; once it reaches 0x800,
 * advance to the next state. */
extern void func_0203c640(int a);
void func_ov235_020d1cb4(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 8) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 8) = t;
    if (t < 0x800) return;
    func_0203c640(param_1);
}
