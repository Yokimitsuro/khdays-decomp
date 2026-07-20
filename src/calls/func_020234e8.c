extern unsigned short data_0204be08;
extern unsigned short data_0204be08_alias;

extern int func_02030788(void);
extern short func_02031384(int a, void *b, int c);
extern void func_ov023_02083aa8(void);
extern void func_020235e8(int flag, int a, int b);

void func_020234e8(void) {
    char *self = *(char **)((char *)&data_0204be08 + 4);

    if (func_02030788() != 0) {
        return;
    }
    if ((&data_0204be08)[1] != 1) {
        return;
    }
    if (data_0204be08 != 0) {
        return;
    }

    data_0204be08 = 1;
    func_02031384(0x11, (void *)&data_0204be08_alias, 2);
    func_ov023_02083aa8();
    func_020235e8(0x2484, 1, 1);
    *(int *)(self + 0xe8) = 1;
}
