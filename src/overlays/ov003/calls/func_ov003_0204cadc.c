extern char data_ov003_0204f9a0[];

int func_ov003_0204cadc(int param) {
    int r = 0;
    switch (*(unsigned short *)(*(int *)data_ov003_0204f9a0)) {
    case 1:
        r = 0xc;
        break;
    case 2:
        r = param * 0xc + 6;
        break;
    case 3:
        r = param * 0xa + 2;
        break;
    case 4:
        r = param << 3;
        break;
    }
    return r;
}
