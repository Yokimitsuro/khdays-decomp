/* Unless the busy byte at *(child+8) is set, invoke func_0203c640. */
extern void func_0203c640(int a);
void func_ov244_020cf14c(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 8) != 0) return;
    func_0203c640(param_1);
}
