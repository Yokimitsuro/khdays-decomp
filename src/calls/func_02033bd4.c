extern void func_02019eac(int index, int value);

void func_02033bd4(void) {
    int index;

    for (index = 2; index < 0x20; index++) {
        func_02019eac(index, 0);
    }
}
