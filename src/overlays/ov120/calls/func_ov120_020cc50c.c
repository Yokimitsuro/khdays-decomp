extern void func_0203c5c0();
extern void func_ov120_020cc7d0(void);

void func_ov120_020cc50c(int this_) {
    int *result;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x50, func_ov120_020cc7d0, 0, &result);
    *result = this_;
    result[1] = *(int *)(*result + 0x384);
    *(int **)(this_ + 0x214) = result;
}
