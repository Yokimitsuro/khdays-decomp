extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov241_020d0940();

void func_ov241_020d08ec(int this_) {
    int a = *(int *)this_;
    int b = *(int *)(this_ + 4);
    int obj;
    *(int *)(b + 0x2c) = *(int *)(b + 0x2c) - *(int *)(a + 0x2c);
    obj = *(int *)b;
    if (*(unsigned char *)(*(int *)(obj + 0x384) + 0xad) != 0) return;
    func_ov107_020c9264(obj, 6, 0);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov241_020d0940);
}
