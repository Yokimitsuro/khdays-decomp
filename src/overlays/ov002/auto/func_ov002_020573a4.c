extern int data_ov002_0207f614;

int func_ov002_020573a4(void) {
    int r = 1;
    int v = *(int *)(*(int *)&data_ov002_0207f614 + 0x18c);
    if (v < 9) {
        return r;
    }
    if (v <= 0xb) {
        r = 0;
    }
    return r;
}
