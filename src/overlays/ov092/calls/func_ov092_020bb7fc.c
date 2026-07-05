extern int func_02023c40(int p);
extern void func_ov022_020a35f4(int a, int b);
extern int data_ov092_020bc4e0;

void func_ov092_020bb7fc(int this_, int arg1) {
    int p = data_ov092_020bc4e0 + 0x194;
    int base = p + 0x2c00;
    int r = func_02023c40(p);
    *(int *)(base + 0x130) = (r == 1) ? 0x171 : 0xf6;
    *(int *)base = arg1;
    func_ov022_020a35f4(this_, 0x21);
}
