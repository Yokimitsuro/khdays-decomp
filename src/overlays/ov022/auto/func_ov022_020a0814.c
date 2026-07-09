int func_ov022_020a0814(int arg0) {
    unsigned short f = *(unsigned short *)(arg0 + 0x1a);
    int r = -1;
    int cnt = 0;
    if ((f & 0x40) != 0) {
        r = 0;
        cnt++;
    } else if ((f & 0x80) != 0) {
        cnt++;
        r = 0x8000;
    }
    if ((f & 0x20) != 0) {
        r += 0x4000;
        cnt++;
    } else if ((f & 0x10) != 0) {
        if ((f & 0x40) != 0) r += 0x1c000;
        else r += 0xc000;
        cnt++;
    }
    if (cnt > 1) r >>= 1;
    return r;
}
