extern int func_0200ca7c(void);
extern void func_0200d138(unsigned int cmd);

struct CC {
    char _0[0x20];
    int field_20;
    int field_24;
};
extern struct CC data_020463cc;

int func_0200ce34(int arg0, int arg1, int arg2, int arg3)
{
    if (func_0200ca7c() == 0) return 1;
    data_020463cc.field_20 = arg2;
    data_020463cc.field_24 = arg3;
    func_0200d138((arg0 & 0xff) | 0x02006400);
    func_0200d138(0x01010000 | (arg1 & 0xffff));
    return 0;
}
