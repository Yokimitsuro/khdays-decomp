extern int func_ov025_02084afc();
extern int func_ov025_020a4d94();
extern int func_ov025_020a41f0();
extern int func_ov025_020a4970();

void func_ov025_02099230(int arg0) {
    int x = func_ov025_02084afc(arg0);
    if (*(int *)(x + 0x30) != 0) {
        return;
    }
    *(int *)(x + 0x24) = 1;
    func_ov025_020a4d94(0);
    func_ov025_020a41f0(0x14, 0, 5);
    func_ov025_020a4970();
}
