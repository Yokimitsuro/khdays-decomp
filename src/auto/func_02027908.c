void func_02027908(int *a, int *b, int scale, int flag) {
    if (flag) {
        a[0] += scale;
        a[1] += scale;
        a[2] += scale;
    } else {
        a[0] += (scale * b[0]) >> 12;
        a[1] += (scale * b[1]) >> 12;
        a[2] += (scale * b[2]) >> 12;
    }
}
