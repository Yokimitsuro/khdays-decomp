int func_02025818(int *arg0, short arg1) {
    if (arg0[0] != 0) {
        *(short *)arg0[1] = arg1;
        arg0[0] -= 1;
    }
    arg0[1] += 2;
}
