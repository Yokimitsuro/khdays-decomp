extern int data_ov021_02080f40;
extern int func_ov002_02076a80();

void func_ov021_02080c40(int this_) {
    int i;
    if (data_ov021_02080f40 == 0) return;
    for (i = 0; i < (int)*(unsigned short *)(data_ov021_02080f40 + 0x50); i++) {
        int r = func_ov002_02076a80(data_ov021_02080f40, i);
        if (r != this_) {
            *(int *)(r + 0x2b8) = 0x12c000;
        }
    }
}
