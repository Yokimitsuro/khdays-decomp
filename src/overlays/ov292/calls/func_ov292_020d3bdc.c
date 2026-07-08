extern void func_0203c5c0();
extern void func_ov292_020d4030(void);

void func_ov292_020d3bdc(int this_) {
    int *result;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x5c, func_ov292_020d4030, 0, &result);
    *result = this_;
    result[1] = *(int *)(*result + 0x384);
    *(int **)(this_ + 0x214) = result;
}
