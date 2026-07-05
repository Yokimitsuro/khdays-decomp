extern void func_0203c5c0();
extern void func_ov133_020d25f4(void);

void func_ov133_020d22a0(int this_) {
    int *result;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x60, func_ov133_020d25f4, 0, &result);
    *result = this_;
    result[1] = *(int *)(*result + 0x384);
    *(int **)(this_ + 0x214) = result;
}
