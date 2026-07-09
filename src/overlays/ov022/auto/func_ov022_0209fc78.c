int func_ov022_0209fc78(int arg0, int arg1) {
    int r;
    int i;
    if (arg1 >= 0) return *(char *)(arg1 * 0x164 + arg0 + 0xda9) != 0;
    r = 0;
    i = 0;
    do {
        if (*(char *)(arg0 + 0xda9) != 0) {
            r = 1;
            break;
        }
        i++;
        arg0 += 0x164;
    } while (i < 2);
    return r;
}
