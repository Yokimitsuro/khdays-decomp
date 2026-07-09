extern int func_ov025_02084afc();
extern int func_02033b78();
extern int func_ov025_020a076c();

void func_ov025_020a01bc(int arg0) {
    int x = func_ov025_02084afc(arg0);
    if (*(unsigned short *)*(int *)(x + 0x204) == 0) {
        return;
    }
    func_02033b78(0, 0);
    func_ov025_020a076c();
    *(unsigned char *)(x + 0x22c) ^= 1;
}
