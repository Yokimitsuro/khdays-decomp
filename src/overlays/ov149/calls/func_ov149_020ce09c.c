extern int func_ov107_020c9ec8();
extern int func_ov107_020c6980();
extern int func_0203c960();
extern int func_0203ca30();
extern int func_0203c9d0();

void func_ov149_020ce09c(char *obj, int arg1) {
    func_ov107_020c9ec8(*(int *)(obj + 0x3cc));
    func_ov107_020c6980(obj, arg1);
    func_0203c960(obj + 0x39c);
    func_0203ca30(obj + 0x39c, *(int *)(obj + 0x394) + 0x14);
    func_0203c9d0(obj + 0x39c, obj + 0xa0);
}
