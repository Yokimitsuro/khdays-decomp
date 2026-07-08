extern void func_0203c5c0();
extern void func_ov297_020d4308(void);

void func_ov297_020d3d90(int this_) {
    int *result;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x94, func_ov297_020d4308, 0, &result);
    *result = this_;
    result[1] = *(int *)(*result + 0x384);
    *(int **)(this_ + 0x214) = result;
}
