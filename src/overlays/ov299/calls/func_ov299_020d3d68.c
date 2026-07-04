extern void func_ov107_020c5c54();
extern void func_ov299_020d410c();

void func_ov299_020d3d68(int this_, int arg1, int arg2, int arg3) {
    func_ov107_020c5c54(this_, arg1);
    if (*(int *)(this_ + 0x50) != 1) return;
    func_ov299_020d410c(*(int *)(this_ + 0x214), arg2, arg3);
}
