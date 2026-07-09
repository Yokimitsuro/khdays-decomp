int func_ov022_02085cc0(int *arg0, int *arg1) {
    int ip = 0;
    if (arg0[2] == 0) ip = 1;
    if (arg1[1] > arg0[1]) ip = 1;
    else if (arg1[1] == arg0[1]) {
        if (arg1[0] < arg0[0]) ip = 1;
    }
    return ip;
}
