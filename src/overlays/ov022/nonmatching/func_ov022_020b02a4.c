char *func_ov022_020b02a4(int obj, int param2) {
    char *slot = (char *)(obj + 0x1a8);
    char *result = 0;
    int i = 0;
    do {
        if (*slot == -1) { *slot = (char)param2; result = slot; break; }
        if (*slot == param2) { result = slot; break; }
        slot += 0x2c;
        i++;
    } while (i < 0x10);
    return result;
}
