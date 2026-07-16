void func_ov008_0205e7ec(int arg0, int arg1) {
    if (*(int *)(arg0 + 0x10) != 2 && *(int *)(arg0 + 0x28) == 0) return;
    *(unsigned int *)(arg0 + 0x1ba4 + (arg1 / 32) * 4) |= 1 << (arg1 % 32);
}
