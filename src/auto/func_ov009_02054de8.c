int func_ov009_02054de8(int arg0) {
    int count = 0;
    do {
        arg0 = arg0 / 10;
        count = count + 1;
    } while (arg0 > 0);
    return count;
}
