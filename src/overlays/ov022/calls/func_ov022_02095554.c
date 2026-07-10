extern int func_ov022_02095618(int arg0);

int func_ov022_02095554(unsigned int *arg0) {
    if (arg0[1] != 9 && (arg0[1] != 6 || (*arg0 & 0x200) == 0)) {
        return 0;
    }
    if (func_ov022_02095618((int)arg0) == 2 && (int)arg0[0xcb] >= (int)arg0[0xce]) {
        return 1;
    }
    return 0;
}
