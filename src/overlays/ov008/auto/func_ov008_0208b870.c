int func_ov008_0208b870(char *obj) {
    if (*(unsigned short *)(*(int *)obj + 2) != 0x15) {
        return 0;
    }
    *(int *)obj = 0;
    return 1;
}
